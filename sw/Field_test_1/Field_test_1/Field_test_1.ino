
void setup() {
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 0\r\n");  // Set *RRN response to include minimum data (only the two IDs, signal strength, and distance)
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312AF8\r\n");   //Set cow to blink every 11000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312EE0\r\n");   //Set other remote node to blink every 12000 ms
  Serial1.print("SDAT 0 000009EEEE95 0B 08125554025500033132C8\r\n");   //Set other remote node to blink every 13000 ms
}

//global variables
char IDblink[39] = {'\0'};  // IDblink (*RRN response) is 39 characters
int NumCows = 1;  //Will need this variable to index the CowDistanceMatrix
//float CowDistanceMatrix[1][4] = {55.17,51.225,86.28,48.42}; //Known distances, output should be around (40,38)
//float CowDistanceMatrix[1][4] = {39.4,56.85,103,44.4}; //Known distances, output should be around (32.2, 22.9);
float CowDistanceMatrix[1][4];  //General variable to hold distances from each node
float R = 500;                          //maximum system radius

void loop() {
  //Initializing arrays for incoming ID and distance data
  char ID1[] = "000000000002";
  char ID2[] = "000000000022";
  char d[] = "000000";
  
  //Known Beacon IDs
  char b1[] = "000009EEEE95";
  char b2[] = "000009FA68E3";
  char b3[] = "00002BB8DBE4";
  char b4[] = "0000025DEE6B";
  
  //Known Cow ID
  char cow[] = "0000112A7CCA";

  //Loop to parse *RRN command into IDblink variable
  while (Serial1.available()) {
    int bad=0;
    char c = Serial1.read();
    if (c == '*') {   
      while (!Serial1.available()) {
          //Wait for a Response
        }
      char c1 = Serial1.read();
      if (c1 == 'R'){                     //Node ID Blink Found
        IDblink[0] = c;                   //Set first two characters in Node ID Blink
        IDblink[1] = c1;
        
        //Loop through 37 times to get the entire string because the string is 39 characters and we use i+2
        for (int i = 0; i < 37; i++) {
          
        while (!Serial1.available()) {
          //Wait for a Response
        }
        
        c = Serial1.read();               //Keep Reading in Node ID 
        if (c=='*'){  //overlapping ID blinks
          bad = 1;  //variable to check for overlapping *RRN commands
          break;
        }
        
        IDblink[i + 2] = c; //Fill IDblink with data read from serial port
      }
      
      if (bad==1){    //Exit while loop if overlapping *RRN commands ... will start over with new IDblink
        //Serial.println("overlap");
        continue;
      }
  
      //Seperates and Saves IDblink into Components and prints each component one char at a time
      //First Node ID
      for (int i = 0; i < 12; i++) {
        ID1[i] = IDblink[i + 5];
      }
      Serial.print("ID1 before function = ");
      Serial.println(ID1);

      //Second Node ID
      for (int i = 0; i < 12; i++) {
        ID2[i] = IDblink[i + 18];
      }
      Serial.print("ID2 before function = ");
      Serial.println(ID2);
      
      //Distance value in cm
      for (int i = 0; i < 6; i++) {
        d[i] = IDblink[i + 33];
     }
     Serial.print("distance = ");
     Serial.print(d);
     Serial.println(" centimeters");

      // Check that one ID is a cow
      if ((strcmp(ID1, cow) == 0)||(strcmp(ID2, cow) == 0)){
       //cow_distance(d, b1, b2, b3, b4, ID1, ID2, cow);   //Call function if one ID is a cow
      }
      
      Serial.print("the cow matrix is: ");
      int checkmatrix=0;
      for (int i=0; i<4;i++){
        Serial.print(CowDistanceMatrix[0][i]);
        Serial.print(" ");
        if (CowDistanceMatrix[0][i]!=0.00){
          checkmatrix=checkmatrix+1;
        }
      }
      Serial.println();
      Serial.print("the matrix is this full: ");
      Serial.println(checkmatrix);

      //If distance matrix has 3 or more distances, then call the trilateration function
      if (checkmatrix>2){
        //Data Validation (Exceeding Results)
        for (int j=0; j<NumCows; j++){    //Loop through number of cows
          for( int i=0; i<4;i++){         //Loop through 4 distances in the matrix
            if (CowDistanceMatrix[j][i]>R){   //If any of the distances are greater than R (the range of the beacons) set them to 0
              CowDistanceMatrix[j][i]=0.0;
              Serial.print("D of i exceeds radius value when i = ");  
              Serial.println(i);
              }
            }
          }
        trilateration();  //Call trilateration function if there are 3 or more distances
      }
    }
   
    }
  }
  
}
