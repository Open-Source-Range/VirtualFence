void IDBlink() {
  //Makes Nanotron Responsive
  Serial1.write("RATO 0 0000112A7CCA \n\r");

  //Collects IDblink Information
  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '*') {
      char IDblink[39];
      IDblink[0] = c;
      for (int i = 0; i < 38; i++) {
        while (!Serial1.available()) {
          //Wait for a Response
        }
        c = Serial1.read();
        IDblink[i + 1] = c;
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
      if ((strcmp(ID1, b1) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b1) == 0)) {
        Serial.println("Beacon 1 to Cow Sucess!!!");
        Serial.print('\n');
        for (int i = 0; i < 6; i++) {
          db1[i] = d[i];
        }
      }
      else if ((strcmp(ID1, b2) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b2) == 0)) {
        Serial.println("Beacon 2 to Cow Sucess!!!");
        Serial.print('\n');
        for (int i = 0; i < 6; i++) {
          db2[i] = d[i];
        }
      }
      else if ((strcmp(ID1, b3) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b3) == 0)) {
        Serial.println("Beacon 3 to Cow Sucess!!!");
        Serial.print('\n');
        for (int i = 0; i < 6; i++) {
          db2[i] = d[i];
        }
      }
    }
    else {
      continue;
    }
  }
  delay(1000);

}
