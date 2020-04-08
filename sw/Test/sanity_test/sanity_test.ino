void setup() {
  // put your setup code here, to run once:
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("NCFG 0\r\n");  // Set *RRN response to include minimum data
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312AF8\r\n");   //Set cow to blink every 11000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312710\r\n");   //Set other remote node to blink every 10000 ms
}

void loop() {
 //Arrays for incoming data
/*
 
  char IDblink[39]; // IDblink (*RRN response) is 39 characters, plus 6 possible spaces (so 45 total)
  char ID1[13];
  char ID2[13];
  char d[6];
  //Other Variables
  int NumCows = 3;
  int track = 0;
  //Known Beacon ID's
  //char b1[12] = "000009EEEE95";
  //char b2[12] = "000009FA68E3";
  //char b3[12] = "11002BB8DBE4";
  //char b4[12] = "0000112A7CCA";

 
  
  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '*') {
      while (!Serial1.available()) {
          //Wait for a Response
        }
      char c1 = Serial1.read();
      if (c1 == 'R'){                     //Node ID Blink Found
        IDblink[0] = c;                   //Set first two characters in Node ID Blink
        IDblink[1] = c1;
        for (int i = 0; i < 37; i++) {
        while (!Serial1.available()) {
          //Wait for a Response
        }
        c = Serial1.read();               //Keep Reading in Node ID 
        if (c=='\n'){
          IDblink[i+2]=c;
          track=i+2;
          //Serial.println(track);
          break;                          //stop filling out IDBlink at new line
        }
        IDblink[i + 2] = c;
      }
      Serial.println();
      //Print IDblink character by character
      for (int k=0; k<39; k++){
        Serial.print(IDblink[k]);
      }
      Serial.println();
      
      //Seperates and Saves IDblink into Components and prints each component one char at a time
      //First Node ID
      Serial.print("ID1 = ");
      for (int i = 0; i < 12; i++) {
        ID1[i] = IDblink[i + 5];
        ID1[12] = '\0';
        Serial.print(ID1[i]);
      }
      Serial.println();
      
      //Second Node ID
      Serial.print("ID2 = ");
      for (int i = 0; i < 12; i++) {
        ID2[i] = IDblink[i + 18];
        ID1[12] = '\0';
        Serial.print(ID2[i]);
      }
      
      //Distance value in cm
      Serial.println();
      Serial.print("distance = ");
      for (int i = 0; i < 6; i++) {
        d[i] = IDblink[i + 33];
        Serial.print(d[i]);
     }
     Serial.println(" centimeters");
      delay(5000);
    }
    }
  }
*/
  
      char cow[] = "00002BB8DBE4";
      char ID1[] = "00002BB8DBE4";
      //char ID2[] = "0000112A7CCA";
      char ID2[13] ={'0','0','0','1','1','2','A','7','C','C','A','\0'};
      //char ID2[13];
      //strcpy(ID2,ID2t);
      char b1[] = "000009EEEE95";
      char b2[] = "000009FA68E3";
      char b3[] = "11002BB8DBE4";
      char b4[] = "0000112A7CCA";
      //Cow
      Serial.print("cowREGPRINT = ");
      Serial.println(cow);
      delay(500);
      Serial.print("cowLOOP = ");
      for (int i = 0; i < 12; i++) {
        Serial.print(cow[i]);
      }
      Serial.println();
      delay(5000);

      if ((strcmp(ID1, b1) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b1) == 0)) {
          Serial.println("Beacon 1 to Cow Sucess!!!");
          Serial.print('\n');
          //CowDistanceMatrix[i][0] = atol(d);
          //CowDistanceMatrix[i][0] = CowDistanceMatrix[i][0] / 100;
        }
      else if ((strcmp(ID1, b2) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b2) == 0)) {
          Serial.println("Beacon 2 to Cow Sucess!!!");
          Serial.print('\n');
          //CowDistanceMatrix[i][1] = atol(d);
          //CowDistanceMatrix[i][1] = CowDistanceMatrix[i][1] / 100;
        }
        else if ((strcmp(ID1, b3) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b3) == 0)) {
          Serial.println("Beacon 3 to Cow Sucess!!!");
          Serial.print('\n');
          //CowDistanceMatrix[i][2] = atol(d);
          //CowDistanceMatrix[i][2] = CowDistanceMatrix[i][2] / 100;
        }
        else if ((strcmp(ID1, b4) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b4) == 0)) {
          Serial.println("Beacon 4 to Cow Sucess!!!");
          Serial.print('\n');
          //CowDistanceMatrix[i][3] = atol(d);
          //CowDistanceMatrix[i][3] = CowDistanceMatrix[i][3] / 100;
        }
}
