void setup() {
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 0\r\n");  // Set *RRN response to include minimum data
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312AF8\r\n");   //Set cow to blink every 11000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312EE0\r\n");   //Set other remote node to blink every 12000 ms

}

void loop() {
  //float D[4]={55.17,51.225,86.28,48.42}; //Known distances, output should be around (40,38)
  float D[4]={39.4,56.86,102.728,44.4}; //Known distances, output should be around (32.2, 22.9)
  float R=500; //System radius
  float d[4];  //distance compare
  float delta[4]; //temp variable

  delay(7000);
  //Location Arrays
  float x[4][2];
  float y[4][2];

  //beacon coordinates
  float beacon[4][3]={
    0.0, 0.0, 1.0,
    0.0, 70.0, 1.0,
    100.0, 100.0, 1.0,
    70.0, 0.0, 1.0
  };
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

  for (int i=0; i<3; i++){
    if(D[i]>0 && D[i+1]>0){
      
      d[i]=abs(sqrt(pow((beacon[i][0]-beacon[i+1][0]),2)+pow((beacon[i][1]-beacon[i+1][1]),2)));
      if(d[i]>D[i]+D[i+1]){
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
        delta[i]=(.25)*sqrt((d[i]+D[i]+D[i+1])*(d[i]+D[i]-D[i+1])*(d[i]-D[i]+D[i+1])*(-d[i]+D[i]+D[i+1]));
        x[i][0]= ((beacon[i][0]+beacon[i+1][0])/2)+((beacon[i+1][0]-beacon[i][0])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(d[i],2)))-(2*delta[i]*((beacon[i][1]-beacon[i+1][1])/pow(d[i],2)));
        x[i][1]= ((beacon[i][0]+beacon[i+1][0])/2)+((beacon[i+1][0]-beacon[i][0])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(d[i],2)))+(2*delta[i]*((beacon[i][1]-beacon[i+1][1])/pow(d[i],2)));
        y[i][0]= ((beacon[i+1][1]+beacon[i][1])/2)+((beacon[i+1][1]-beacon[i][1])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(d[i],2)))+(2*delta[i]*((beacon[i][0]-beacon[i+1][0])/pow(d[i],2)));
        y[i][1]= ((beacon[i+1][1]+beacon[i][1])/2)+((beacon[i+1][1]-beacon[i][1])*(pow(D[i],2)-pow(D[i+1],2))/(2*pow(d[i],2)))-(2*delta[i]*((beacon[i][0]-beacon[i+1][0])/pow(d[i],2)));
      }
    }
    else{
      Serial.println("Should not make it here");
      x[i][0]=0;
      x[i][1]=0;
      y[i][0]=0;
      y[i][1]=0;
    }
    Serial.print("i = ");
    Serial.println(i);
    Serial.print("d[i] = ");
    Serial.println(d[i]);
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

  for (int i=0; i<4; i++){
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

Serial.print("tx = ");
Serial.println(tx);
Serial.print("ty = ");
Serial.println(ty);
Serial.print("Xf = ");
Serial.println(Xf);
Serial.print("Yf = ");
Serial.println(Yf);
}
