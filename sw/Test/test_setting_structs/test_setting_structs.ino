const int NumCows=1;
const int NumBeaks=4;

//Data Structures

// Structure for location of a beacon
struct beacon_loc {
  char BID[12];
  float x, y, z;
};

//Stucture for a cow distance
struct cow_dist{
  char CID[12];
  float d = 0;
  int t;
  int valid = 0;
};

//Structure for a cow location
struct cow_loc{
  char  CID[12];
  float x, y, z;
  int valid = 0;
};

//Structure for a beacon that holds an array of 
//structures of distances to each cow
class beacon_cows{
  public:
  char BID[12]="111111111111";
  cow_dist cows[NumCows];
};

//Array of indexes of my four local beacons
//Gives index to use for bl_array
int my_beaks[4];

//Array of cow location structures
//Stores all cow locations
cow_loc cow_loc_array[NumCows];

//Array of all beacon location structures
beacon_loc bl_array[NumBeaks];

//Declare 4 beacon_cow objects
//One for each of the 4 local beacons

//B_2, B_3, B_4;



void setup() {
 #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 4\r\n");  // Set *RRN response to include RSSI data
  Serial1.print("SBIV 60000\r\n");  //Set host to blink every minute
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003311388\r\n");   //Set cow to blink every 5000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003317530\r\n");   //Set other remote node to blink every minute
}

void loop() {
  

beacon_cows beacon1;
for (int i=0; i<12; i++){
  beacon1.BID[i] = 'A';
}
  Serial.print("beacon1 = ");
  Serial.println(beacon1.BID);
  delay(1000000);
}
