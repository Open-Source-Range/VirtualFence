//Associating Beacon to Cow Distance Function
void cow_distance(char d[6], char b1[], char b2[], char b3[], char b4[], char ID1[], char ID2[], char cow[]){
      Serial.println("Hello from cow_distance");
      
      // Check the strings then convert d to a float, divide by 100 to get meters, and add to the corresponding element in the CowDistanceMatrix
        if ((strcmp(ID1, b1) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b1) == 0)) {
          Serial.println("Beacon 1 to Cow Sucess!!!");  
          float dist = atol(d);
          CowDistanceMatrix[0][0] = dist/100;
        }
        else if ((strcmp(ID1, b2) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b2) == 0)) {
          Serial.println("Beacon 2 to Cow Sucess!!!");
          float dist = atol(d);
          CowDistanceMatrix[0][1] = dist/100;
        }
        else if ((strcmp(ID1, b3) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b3) == 0)) {
          Serial.println("Beacon 3 to Cow Sucess!!!");
          float dist = atol(d);
          CowDistanceMatrix[0][2] = dist/100;
        }
        else if ((strcmp(ID1, b4) == 0 && strcmp(ID2, cow) == 0) || (strcmp(ID1, cow) == 0 && strcmp(ID2, b4) == 0)) {
          Serial.println("Beacon 4 to Cow Sucess!!!");
          float dist = atol(d);
          CowDistanceMatrix[0][3] = dist/100;
        }
        Serial.println();
}
