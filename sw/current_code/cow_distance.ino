//Associating Beacon to Cow Distance Function
void cow_distance(char d[6], char ID1[], char ID2[], int i, int k, char fakecow[]){
      //Serial.println("Hello from cow_distance");
      Serial.println();
      int thiscow;
      // Check the strings then convert d to a float, divide by 100 to get meters, and add to the corresponding element in the CowDistanceMatrix
        if (k==0) {
          Serial.print("Beacon 0 to Cow ");
          Serial.print(i);
          Serial.println(" Sucess!!!");  
          float dist = atol(d);
          //for (int j=0; j<NumCows; j++){
            //if (strcmp(fakecow, beacon_array[0].cows[j].CID)==0){
              beacon_array[0].cows[i].d_cd = dist/100.0;
              beacon_array[0].cows[i].t = millis();
              //thiscow = j;
            //}
          //}
          Serial.print("Distances to this cow are now: ");
          Serial.println(beacon_array[0].cows[i].d_cd);
          Serial.println(beacon_array[1].cows[i].d_cd);
          Serial.println(beacon_array[2].cows[i].d_cd);
          Serial.println(beacon_array[3].cows[i].d_cd);
        }
        else if (k == 1) {
          Serial.print("Beacon 1 to Cow ");
          Serial.print(i);
          Serial.println(" Sucess!!!");
          float dist = atol(d);
          //CowDistanceMatrix[0][1] = dist/100;
          //for (int j=0; j<NumCows; j++){
            //if (strcmp(fakecow, beacon_array[1].cows[j].CID)==0){
              beacon_array[1].cows[i].d_cd = dist/100.0;
              beacon_array[1].cows[i].t = millis();
             // thiscow = j;
           // }
          //}
          Serial.print("Distances to this cow are now: ");
          Serial.println(beacon_array[0].cows[i].d_cd);
          Serial.println(beacon_array[1].cows[i].d_cd);
          Serial.println(beacon_array[2].cows[i].d_cd);
          Serial.println(beacon_array[3].cows[i].d_cd);
        }
        else if (k == 2) {
          Serial.print("Beacon 2 to Cow ");
          Serial.print(i);
          Serial.println(" Sucess!!!");
          float dist = atol(d);
          //CowDistanceMatrix[0][2] = dist/100;
          //for (int j=0; j<NumCows; j++){
           // if (strcmp(fakecow, beacon_array[2].cows[j].CID)==0){
              beacon_array[2].cows[i].d_cd = dist/100.0;
              beacon_array[2].cows[i].t = millis();
              //thiscow = j;
            //}
         // }
          Serial.print("Distances to this cow are now: ");
          Serial.println(beacon_array[0].cows[i].d_cd);
          Serial.println(beacon_array[1].cows[i].d_cd);
          Serial.println(beacon_array[2].cows[i].d_cd);
          Serial.println(beacon_array[3].cows[i].d_cd);
        }
        else if (k == 3){
          Serial.print("Beacon 3 to Cow ");
          Serial.print(i);
          Serial.println(" Sucess!!!");
          float dist = atol(d);
          //for (int j=0; j<NumCows; j++){
            //if (strcmp(fakecow, beacon_array[3].cows[j].CID)==0){
              beacon_array[3].cows[i].d_cd = dist/100.0;
              beacon_array[3].cows[i].t = millis();
              //thiscow=j;
            //}
          //}
          Serial.print("Distances to this cow are now: ");
          Serial.println(beacon_array[0].cows[i].d_cd);
          Serial.println(beacon_array[1].cows[i].d_cd);
          Serial.println(beacon_array[2].cows[i].d_cd);
          Serial.println(beacon_array[3].cows[i].d_cd);
        }
        Serial.println();
}
