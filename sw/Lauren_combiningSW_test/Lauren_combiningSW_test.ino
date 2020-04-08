#include <string.h>

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("NCFG 0\r\n");  // Set *RRN response to include minimum data
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312710\r\n");   //Set cow to blink every 10000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312AF8\r\n");   //Set other remote node to blink every 11000 ms
}



//Known Beacon ID's
  char b1[14] = "000009EEEE95";
  char b2[14] = "000009FA68E3";
  char b3[14] = "00002BB8DBE4";
  char b4[14] = "100009FA68E3";

//Known Beacon Locations [X,Y,Z]
  float BeaconLocationMatrix[4][3] = {{0,0,1},
                                      {1,70,1},
                                      {70,70,1},
                                      {70,0,1}};

//Known Cow ID's
  char cow[][14] = {{"0000112A7CCA"},
                    {"0000123456AS"},
                    {"000098765432"}};
  int NumCows = 3;
  
//Distance Matrix   !!! [X][Y] ---> Change the X value to be equal to NumCows !!!
  float CowDistanceMatrix[3][4];

//Extracted ID's and current distance from IDblink
  char ID1[14];
  char ID2[14];
  char d[7];

//IDblink Variables
  char IDblink[39];

//Cow Location Matrix rows-->[ID] columns-->[x][y]
//Change the X value to be equal to NumCows !!!
  float LocationMatrix[3][2];
  float HoldX = 0;
  float HoldY = 0;
  float D[4];

void loop() {
  // Gathers distances from Nanotron Network
  IDBlink1();

  //Checking for Valid Amount of Data and Calculating X,Y coordinates
  for (int i = 0; i < NumCows; i++) {
    if (CowDistanceMatrix[i][0] > 0 && CowDistanceMatrix[i][1] > 0 && CowDistanceMatrix[i][2] > 0 || 
        CowDistanceMatrix[i][0] > 0 && CowDistanceMatrix[i][1] > 0 && CowDistanceMatrix[i][3] > 0 || 
        CowDistanceMatrix[i][0] > 0 && CowDistanceMatrix[i][2] > 0 && CowDistanceMatrix[i][3] > 0 ||
        CowDistanceMatrix[i][1] > 0 && CowDistanceMatrix[i][2] > 0 && CowDistanceMatrix[i][3] > 0 ){
          D[0] = CowDistanceMatrix[i][0];
          D[1] = CowDistanceMatrix[i][1];
          D[2] = CowDistanceMatrix[i][2];
          D[3] = CowDistanceMatrix[i][3];
          //Location();
         // LocationMatrix[i][0] = HoldX;
          //LocationMatrix[i][1] = HoldY;  
        }
  }






  
}
