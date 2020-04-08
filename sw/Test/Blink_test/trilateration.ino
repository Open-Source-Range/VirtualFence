
void trilateration(void){
  Serial.println("Distance is not 0, yay!");
  float D[8];
  
  for (int i=0;i<4;i++){
    D[i]=CowDistanceMatrix[0][i];
    Serial.print("i = ");
    Serial.println(i);
    Serial.print("D[i] = ");
    Serial.println(D[i]);
    Serial.print("CowMatrix[0][i] = ");
    Serial.println(CowDistanceMatrix[0][i]);
    CowDistanceMatrix[0][i]=0; 
    Serial.print("CowMatrix[0][i] = ");
    Serial.println(CowDistanceMatrix[0][i]);
  }
  D[4]=D[0];
  D[5]=D[1];
  D[6]=D[2];
  D[7]=D[3];
  
  Serial.println();
  
  float R=500; //System radius
  float dd[8];  //distance compare
  float delta[8]; //temp variable

  delay(7000);
  //Location Arrays
  float x[8][2];
  float y[8][2];

  //beacon coordinates
   //for the field tests:
  float beacon[8][3]={
    0.0, 0.0, 1.0,
    0.0, 70.0, 1.0,
    100.0, 100.0, 1.0,
    70.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 70.0, 1.0,
    100.0, 100.0, 1.0,
    70.0, 0.0, 1.0
  };/*
  float beacon[8][3]={
    2.8, 2.5, 1.0,
    0.0, 0.0, 1.0,
    0.15, 4.5, 1.0,
    3.0, 0.0, 1.0,
    2.8, 2.5, 1.0,
    0.0, 0.0, 1.0,
    0.15, 4.5, 1.0,
    3.0, 0.0, 1.0
  };*/
/* check for correct beacon assignment
  Serial.print("beacon[0][0] = ");
  Serial.println(beacon[0][0]);
  Serial.print("beacon[3][0] = ");
  Serial.println(beacon[3][0]);
  Serial.print("beacon[2][1] = ");
  Serial.println(beacon[2][1]);
*/
  delay(1000);
  
  //Data Validation (Exceeding Results)
  for (int i=0; i<4; i++){
    if (D[i]>R){
      D[i]=0;
      Serial.print("D of i exceeds radius value when i = ");
      Serial.println(i);
    }
  }
  
  //Data Validation (Looking for minimum data points)
  if (D[0]==0 && D[1]==0 || D[1]==0 && D[2]==0 || D[2]==0 && D[3]==0 || D[3]==0 && D[0]==0){
    Serial.println("Error, Multiple Solutions Exist");
  }

  // Beacon reassignment for code iterations

  //X, Y Calculations
  for (int i=0; i<8; i++){
   if(D[i]>0 && D[i+1]>0){
      
      dd[i]=abs(sqrt(pow((beacon[i][0]-beacon[i+1][0]),2)+pow((beacon[i][1]-beacon[i+1][1]),2)));
      if(dd[i]>D[i]+D[i+1]){
        Serial.print("Error No Solutions Exist between ");
        Serial.print(i);
        Serial.print(" and ");
        Serial.println(i+1);
        x[i][0]=0;
        x[i][1]=0;
        y[i][0]=0;
        y[i][1]=0;
      }
      else {
        delay(1000);
        delta[i]=(.25)*sqrt((dd[i]+D[i]+D[i+1])*(dd[i]+D[i]-D[i+1])*(dd[i]-D[i]+D[i+1])*(-dd[i]+D[i]+D[i+1]));
        x[i][0]= ((beacon[i][0]+beacon[i+1][0])/2)+((beacon[i+1][0]-beacon[i][0])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(dd[i],2)))-(2*delta[i]*((beacon[i][1]-beacon[i+1][1])/pow(dd[i],2)));
        x[i][1]= ((beacon[i][0]+beacon[i+1][0])/2)+((beacon[i+1][0]-beacon[i][0])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(dd[i],2)))+(2*delta[i]*((beacon[i][1]-beacon[i+1][1])/pow(dd[i],2)));
        y[i][0]= ((beacon[i+1][1]+beacon[i][1])/2)+((beacon[i+1][1]-beacon[i][1])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(dd[i],2)))+(2*delta[i]*((beacon[i][0]-beacon[i+1][0])/pow(dd[i],2)));
        y[i][1]= ((beacon[i+1][1]+beacon[i][1])/2)+((beacon[i+1][1]-beacon[i][1])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(dd[i],2)))-(2*delta[i]*((beacon[i][0]-beacon[i+1][0])/pow(dd[i],2)));
      }
    }
    else{
      Serial.print("Now x and y for i = ");
      Serial.print(i);
      Serial.println(" are 0");
      x[i][0]=0;
      x[i][1]=0;
      y[i][0]=0;
      y[i][1]=0;
    }
    Serial.print("i = ");
    Serial.println(i);
    Serial.print("dd[i] = ");
    Serial.println(dd[i]);
    Serial.print("delta[i] = ");
    Serial.println(delta[i]);
    Serial.print("x[i][0] = ");
    Serial.println(x[i][0]);
    Serial.print("x[i][1] = ");
    Serial.println(x[i][1]);
    Serial.print("y[i][0] = ");
    Serial.println(y[i][0]);
    Serial.print("y[i][1] = ");
    Serial.println(y[i][1]);
  }
  
  //Final Location Arrays
  float Xf = 0;
  float Yf = 0;
  float ty=0;
  float tx=0;

  for (int i=0; i<8; i++){
    if (y[i][0] > 0){
      //Serial.print("y[i][0] should be greater than 0: ");
      //Serial.println(y[i][0]);
      Yf = Yf + y[i][0];
      ty=ty+1;
    }
    if (x[i][0] > 0){
      Xf = Xf + x[i][0];
      tx = tx+1;
    }
}

Xf = Xf/tx;
Yf = Yf/ty;
/*
//Averaging to Include Cross Data
for(int i=0; i++; i<2){
  if(x[4][i]>=Xf+5 && x[4][i] <= Xf+5){
    Xf = (Xf+x[4][i])/2;    
    Serial.println("x[4]?");

  }
  if(x[6][i]>=Xf+5 && x[6][i] <= Xf+5){
    Xf = (Xf+x[6][i])/2;
    Serial.println("x[6]?");

  }
}

for(int i=0; i++; i<2){
  if(y[4][i]>=Yf+5 && y[4][i] <= Yf+5){
    Yf = (Yf+y[4][i])/2;
    Serial.println("y[4]?");

  }
  if(y[6][i]>=Yf+5 && y[6][i] <= Yf+5){
    Yf = (Yf+y[6][i])/2;
    Serial.println("y[6]?");
  }
}
*/
Serial.print("tx = ");
Serial.println(tx);
Serial.print("ty = ");
Serial.println(ty);
Serial.print("Xf = ");
Serial.println(Xf);
Serial.print("Yf = ");
Serial.println(Yf);

zap(Xf,Yf);
}
