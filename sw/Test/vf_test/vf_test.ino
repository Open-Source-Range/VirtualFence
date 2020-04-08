
#include <string.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
}

int doonce = 1;
int leave = 0;

//Known Beacon ID's
char b1[12] = "000009EEEE95";
//char b2[12] = "100009FA68E3";
char b3[12] = "00000RT93Y05";
char b2[12] = "000009FA68E3";

//Kown Cow ID's
char cow[12] = "0000112A7CCA";

//Distance Variables (char type)
char db1[6] = "AAAAAA";
char db2[6] = "AAAAAA";
char db3[6] = "AAAAAA";

//Distance Variables (int type)
int db1i, db2i, db3i;

//Extracted ID's and current distance from IDblink
String ID1;
String ID2;
String d;

//Filtered IDblink Function Variable
char IDFinal[45];

void loop() {
  //Makes Nanotron Responsive
  if (doonce) {
    Serial1.write("RATO 0 0000112A7CCA \n\r");
    doonce = 1;
  }

  while (Serial1.available() > 0) {
    char c = Serial1.read();
    if (c == '*') {
      char IDblink[45];
      IDblink[0] = c;
      for (int i = 0; i < 44; i++) {
        while (!Serial1.available()) {
          //Wait for a Response
        }
        c = Serial1.read();
        IDblink[i + 1] = c;
      }
      Serial.println(IDblink);









      /*
            for (int i = 0; i < 12; i++) {
              ID1[i] = IDblink[i + 5];
              ID2[i] = IDblink[i + 18];
              if (i < 6) {
                d[i] = IDblink[i + 33];
              }
            }
            /*
              ID1[12]='\n';

              //Serial.println(IDblink);
              /*
              for(int i=0;i<12;i++){
              Serial.print(ID1[i]);
              }
              Serial.print('\n');
              for(int i=0;i<12;i++){
              Serial.print(ID2[i]);
              }
              Serial.print('\n');
              Serial.println(d);
              //Serial.println(IDblink);

              Serial.println(ID1);
              Serial.println(ID2);
              // Serial.println(b1);

              if((strcmp(ID1,b1)==0 && strcmp(ID2,cow)==0) ||(strcmp(ID1,cow)==0 && strcmp(ID2,b1)==0)){
              Serial.print("yes");
              for(int i =0; i <6; i++){
                db1[i]=d[i];
              }
              sscanf(d, "%d", &db1i);
              }
              else if((strcmp(ID1,b2)==0 && strcmp(ID2,cow)==0) ||(strcmp(ID1,cow)==0 && strcmp(ID2,b2)==0)){
              for(int i =0; i <6; i++){
                db2[i]=d[i];
              }
              sscanf(d, "%d", &db2i);
              }
              else if((strcmp(ID1,b3)==0 && strcmp(ID2,cow)==0) ||(strcmp(ID1,cow)==0 && strcmp(ID2,b3)==0)){
              for(int i =0; i <6; i++){
                db3[i]=d[i];
              }
              sscanf(d, "%d", &db3i);
              }
              Serial.println(d);
              //Serial.println(db2i);
              //Serial.println(db3i);
      */
    }
    else {
      continue;
    }

  }
  delay(1000);

}
