void trilateration(int which_cow) {
  Serial.println("Distance is not 0, yay!");
  float D[8];                             //variable to store distance values for looping

  for (int i = 0; i < 4; i++) {
    D[i] = beacon_array[i].cows[which_cow].d_cd;
    beacon_array[i].cows[which_cow].d_cd = 0;         //clears the Distance Matrix after value has been copied for further use
  }

Serial.print("D is : ");
for (int i=0; i<4; i++){
  Serial.println(D[i]);
}
  //Trilateration code loops through the system twice to assure all possible combinations are calculated, this reassigns distances for that loop
  D[4] = D[0];
  D[5] = D[2];
  D[6] = D[3];
  D[7] = D[1];

  float R = 500;                          //maximum system radius
  float dd[8];                            //distance compare to confirm the overlap of two circles
  float delta[8];                         //variable used to reduce x,y equation length
  int sum_tolerance = 5;                  //the tolerance of error allowed when summing all x and y values

  //Location Arrays for ALL x,y coordinate pairs
  float x[8][2];
  float y[8][2];

  //Beacon location Array ... values ARE repeated TWICE
  float beacon[8][3] = {
    0.0, 0.0, 1.0,
    0.0, 70.0, 1.0,
    70.0, 70.0, 1.0,
    51.8, 18.5, 1.0,
    0.0, 0.0, 1.0,
    0.0, 70.0, 1.0,
    70.0, 70.0, 1.0,
    51.8, 18.5, 1.0
  };

  //Data Validation ... Checks to see that the distance provided does not exceed the max range of the nanotron / unreliable
  for (int i = 0; i < 4; i++) {
    if (D[i] > R) {
      D[i] = 0;
    }
  }

  //Data Validation ... Looking for minimum of 3 distance values
  if (D[0] == 0 && D[1] == 0 || D[1] == 0 && D[2] == 0 || D[2] == 0 && D[3] == 0 || D[3] == 0 && D[0] == 0) {
    Serial.println("Error, Multiple Solutions Exist");
  }

  //X,Y Calculations ... confirms that the 2 circles exist and calculates common x,y points / if not, returns a 0
  for (int i = 0; i < 8; i++) {
    if (D[i] > 0 && D[i + 1] > 0) {

      dd[i] = abs(sqrt(pow((beacon[i][0] - beacon[i + 1][0]), 2) + pow((beacon[i][1] - beacon[i + 1][1]), 2)));
      if (dd[i] > D[i] + D[i + 1]) {
        Serial.print("Error No Solutions Exist between ");
        Serial.print(i);
        Serial.print(" and ");
        Serial.println(i + 1);
        x[i][0] = 0;
        x[i][1] = 0;
        y[i][0] = 0;
        y[i][1] = 0;
      }
      else {
        delta[i] = (.25) * sqrt((dd[i] + D[i] + D[i + 1]) * (dd[i] + D[i] - D[i + 1]) * (dd[i] - D[i] + D[i + 1]) * (-dd[i] + D[i] + D[i + 1]));
        x[i][0] = ((beacon[i][0] + beacon[i + 1][0]) / 2) + ((beacon[i + 1][0] - beacon[i][0]) * (pow(D[i], 2) - pow(D[i + 1], 2)) / (2 * pow(dd[i], 2))) - (2 * delta[i] * ((beacon[i][1] - beacon[i + 1][1]) / pow(dd[i], 2)));
        x[i][1] = ((beacon[i][0] + beacon[i + 1][0]) / 2) + ((beacon[i + 1][0] - beacon[i][0]) * (pow(D[i], 2) - pow(D[i + 1], 2)) / (2 * pow(dd[i], 2))) + (2 * delta[i] * ((beacon[i][1] - beacon[i + 1][1]) / pow(dd[i], 2)));
        y[i][0] = ((beacon[i + 1][1] + beacon[i][1]) / 2) + ((beacon[i + 1][1] - beacon[i][1]) * (pow(D[i], 2) - pow(D[i + 1], 2)) / (2 * pow(dd[i], 2))) + (2 * delta[i] * ((beacon[i][0] - beacon[i + 1][0]) / pow(dd[i], 2)));
        y[i][1] = ((beacon[i + 1][1] + beacon[i][1]) / 2) + ((beacon[i + 1][1] - beacon[i][1]) * (pow(D[i], 2) - pow(D[i + 1], 2)) / (2 * pow(dd[i], 2))) - (2 * delta[i] * ((beacon[i][0] - beacon[i + 1][0]) / pow(dd[i], 2)));
      }
    }
    else {
      x[i][0] = 0;
      x[i][1] = 0;
      y[i][0] = 0;
      y[i][1] = 0;
    }
  }

  //Flat X/Y Array Variable
  int MODE_TEMP_ARRAY_X[14];
  int MODE_TEMP_ARRAY_Y[14];

  //Flattens X/Y array for processing
  for (int i = 0; i < 7; i++) {
    MODE_TEMP_ARRAY_X[i] = x[i][0];
    MODE_TEMP_ARRAY_Y[i] = y[i][0];
  }
  for (int i = 0; i < 7; i++) {
    MODE_TEMP_ARRAY_X[i + 7] = x[i][1];
    MODE_TEMP_ARRAY_Y[i + 7] = y[i][1];
  }

  //Counting the Non-0 integers
  int INT_COUNT_X = 0;
  int INT_COUNT_Y = 0;
  for (int i = 0; i < 14; i++) {
    if (MODE_TEMP_ARRAY_X[i] != 0)
      INT_COUNT_X = INT_COUNT_X + 1;
  }
  for (int i = 0; i < 14; i++) {
    if (MODE_TEMP_ARRAY_Y[i] != 0)
      INT_COUNT_Y = INT_COUNT_Y + 1;
  }

  //Getting the final 1-dimensional array with NO 0's
  int MODE_ARRAY_X[INT_COUNT_X];
  int MODE_ARRAY_Y[INT_COUNT_Y];
  
  SORTy(MODE_TEMP_ARRAY_Y, INT_COUNT_Y);
  for (int i = 0; i < INT_COUNT_Y; i++){
    MODE_ARRAY_Y[i] = MODE_TEMP_ARRAY_Y[i];
  }
  
  SORTx(MODE_TEMP_ARRAY_X, INT_COUNT_X);
  for (int i = 0; i < INT_COUNT_X; i++){
    MODE_ARRAY_X[i] = MODE_TEMP_ARRAY_X[i];
  }

  //Getting the MODE
  int MODE_X = 0;
  int MODE_Y = 0;
  MODE_X = mode(MODE_ARRAY_X, INT_COUNT_X);
  MODE_Y = mode(MODE_ARRAY_Y, INT_COUNT_Y);

  
  //Final Location Variable
  float Xf = MODE_X;
  float Yf = MODE_Y;

  //Averages ALL X values into a final answer ... MUST be with sum_tolerance units to be included in final answer
  for (int i = 0; i < 8; i++) {
    if (x[i][0] <= Xf + sum_tolerance && x[i][0] >= Xf - sum_tolerance)
      Xf = (x[i][0] + Xf) / 2;
    if (x[i][1] <= Xf + sum_tolerance && x[i][1] >= Xf - sum_tolerance)
      Xf = (x[i][1] + Xf) / 2;
  }

  //Averages ALL Y values into a final answer ... MUST be with sum_tolerance units to be included in final answer
  for (int i = 0; i < 8; i++) {
    if (y[i][0] <= Yf + sum_tolerance && y[i][0] >= Yf - sum_tolerance)
      Yf = (y[i][0] + Yf) / 2;
    if (y[i][1] <= Yf + sum_tolerance && y[i][1] >= Yf - sum_tolerance)
      Yf = (y[i][1] + Yf) / 2;
  }

  Serial.print("X = ");
  Serial.println(Xf);
  Serial.print("Y = ");
  Serial.println(Yf);

  zap(Xf, Yf);
}
