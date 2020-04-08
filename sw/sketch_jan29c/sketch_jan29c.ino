void IDBlink() {
  
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("NCFG 0\r\n");  // Set *RRN response to include minimum data
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312710\r\n");   //Set cow to blink every 10000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312AF8\r\n");   //Set other remote node to blink every 11000 ms
}

  //Collects IDblink Information
  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '*') {
      char c1 = Serial1.read();
      if (c1 == 'R'){
        char IDblink[39];
        IDblink[0] = c;
        IDblink[1] = c1;
        for (int i = 0; i < 38; i++) {
        while (!Serial1.available()) {
          //Wait for a Response
        }
        c = Serial1.read();
        if (c=='\n'){
          \\then need to stop filling out IDBlink
        }
        }
        IDblink[i + 1] = c;
      }
      }
      

      //Prints IDblink for debugging
      Serial.println(IDblink);

      //Seperates IDblink into Components
      for (int i = 0; i < 12; i++) {
        ID1[i] = IDblink[i + 5];
        ID2[i] = IDblink[i + 18];
      }
      for (int i = 0; i < 6; i++) {
        d[i] = IDblink[i + 33];
      }

      //Print individual Components from IDblink for debugging
      Serial.print("ID1 = ");
      Serial.println(ID1);
      Serial.print("ID2 = ");
      Serial.println(ID2);
      Serial.print("Distance = ");
      Serial.print(d);
      Serial.println(" centimeters");
      Serial.print('\n');

      //Associating Beacon to Cow Distance
      for (int i = 0; i < NumCows; i++) {
        if ((strcmp(ID1, b1) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b1) == 0)) {
          Serial.println("Beacon 1 to Cow Sucess!!!");
          Serial.print('\n');
          CowDistanceMatrix[i][0] = atol(d);
          CowDistanceMatrix[i][0] = CowDistanceMatrix[i][0] / 100;
        }
        else if ((strcmp(ID1, b2) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b2) == 0)) {
          Serial.println("Beacon 2 to Cow Sucess!!!");
          Serial.print('\n');
          CowDistanceMatrix[i][1] = atol(d);
          CowDistanceMatrix[i][1] = CowDistanceMatrix[i][1] / 100;
        }
        else if ((strcmp(ID1, b3) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b3) == 0)) {
          Serial.println("Beacon 3 to Cow Sucess!!!");
          Serial.print('\n');
          CowDistanceMatrix[i][2] = atol(d);
          CowDistanceMatrix[i][2] = CowDistanceMatrix[i][2] / 100;
        }
        else if ((strcmp(ID1, b4) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b4) == 0)) {
          Serial.println("Beacon 4 to Cow Sucess!!!");
          Serial.print('\n');
          CowDistanceMatrix[i][3] = atol(d);
          CowDistanceMatrix[i][3] = CowDistanceMatrix[i][3] / 100;
        }
      }
    }
    else {
      continue;
    }
  }
  //delay(1000);

}
