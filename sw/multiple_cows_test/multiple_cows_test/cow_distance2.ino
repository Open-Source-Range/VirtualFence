//Associating Beacon to Cow Distance Function
void cow_distance2(char d[6], char b1[], char b2[], char b3[], char b4[], char ID1[], char ID2[]){
      Serial.println();
      Serial.println("Hello from cow_distance");

      /*Checking cow information is correct
      Serial.print("cowREGPRINT = ");
      Serial.println(cow);
      delay(500);
      Serial.print("cowLOOP = ");
      for (int i = 0; i < 12; i++) {
        Serial.print(cow[i]);
      }
      Serial.println();
      delay(500);
      */

      //First Node ID
      Serial.print("ID1 in the function = ");
      Serial.println(ID1);
      
      //Second Node ID
      Serial.print("ID2 in the function = ");
      Serial.println(ID2);
       
      //Distance value in cm
      Serial.print("distance = ");
      Serial.print(d);
      Serial.println(" centimeters");
  
      Serial.println();
      delay(500);
      
      /* Printing all strcmp results
      Serial.println("If = 0, then they are the same: ");
      int compare1 = strcmp(ID1,cow);
      int compare2 = strcmp (ID2, cow);
      int compare3 = strcmp(ID1,b2);
      int compare4 = strcmp (ID2, b2);
      int compare5 = strcmp(ID1,b4);
      int compare6 = strcmp (ID2, b4);
      Serial.print("ID1 = cow? ");
      Serial.println(compare1);
      Serial.print("ID2 = cow? ");
      Serial.println(compare2);
      Serial.print("ID1 = b2? ");
      Serial.println(compare3);
      Serial.print("ID2 = b2? ");
      Serial.println(compare4);
      Serial.print("ID1 = b4? ");
      Serial.println(compare5);
      Serial.print("ID2 = b4? ");
      Serial.println(compare6);
      */

      
      // Multiple Cows                       
      for (int i = 0; i < NumCows; i++) {
        if ((strcmp(ID1, b1) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b1) == 0)) {
          Serial.println("Beacon 1 to Cow Sucess!!!");
          Serial.print("for i = ");
          Serial.println(i);
          Serial.print("CowDistanceMatrix[i][0] = ");
          float dist = atol(d);
          CowDistanceMatrix[i][0] = dist/100;
          Serial.println(CowDistanceMatrix[i][0]);
        }
        else if ((strcmp(ID1, b2) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b2) == 0)) {
          Serial.println("Beacon 2 to Cow Sucess!!!");
          Serial.print("for i = ");
          Serial.println(i);
          Serial.print("CowDistanceMatrix[i][1] = ");
          float dist = atol(d);
          CowDistanceMatrix[i][1] = dist/100;
          Serial.println(CowDistanceMatrix[i][1]);
        }
        else if ((strcmp(ID1, b3) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b3) == 0)) {
          Serial.println("Beacon 3 to Cow Sucess!!!");
          Serial.print("for i = ");
          Serial.println(i);
          Serial.print("CowDistanceMatrix[i][2] = ");
          float dist = atol(d);
          CowDistanceMatrix[i][2] = dist/100;
          Serial.println(CowDistanceMatrix[i][2]);
        }
        else if ((strcmp(ID1, b4) == 0 && strcmp(ID2, cow[i]) == 0) || (strcmp(ID1, cow[i]) == 0 && strcmp(ID2, b4) == 0)) {
          Serial.println("Beacon 4 to Cow Sucess!!!");
          Serial.print("for i = ");
          Serial.println(i);
          Serial.print("CowDistanceMatrix[i][3] = ");
          float dist = atol(d);
          CowDistanceMatrix[i][3] = dist/100;
          Serial.println(CowDistanceMatrix[i][3]);
        }
      }
}
/* Set LED based on a Distance Value
  if (CowDistanceMatrix[0][1]>0.00||CowDistanceMatrix[0][2]>0.00){
    Serial1.print("SDAT 1 0000112A7CCA 0B 0812555402550003232710 60000\r\n"); //SSTART command to force receiver active for 60 seconds
    delay(100);
    Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0101000002\r\n"); //Configure GPIO[1] as output with pulldown
    delay(100);
    Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0101\r\n"); //Set pin 1 on remote device high
    delay(1000);
    Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0100\r\n"); //Set pin 1 on remote device low
    delay(350);
  }
*/
