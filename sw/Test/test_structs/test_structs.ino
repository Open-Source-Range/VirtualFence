void setup() {
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 4\r\n");  // Set *RRN response to include RSSI data
  Serial1.print("SBIV 60000\r\n");  //Set host to blink every minute
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003311388\r\n");   //Set cow to blink every 5000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003317530\r\n");   //Set other remote node to blink every minute
  //Serial1.print("SDAT 0 000009EEEE95 0B 0812555402550003317530\r\n");   //Set other remote node to blink every minute


}

const int NumCows = 3;
const int NumBeaks=4;

char b0id[] = "000009FA68E3";
char b1id[] = "000009EEEE95";
char b2id[] = "00002BB8DBE4";
char b3id[] = "0000025DEE6B";

char cow[][12] = {{"0000112A7CCA"},
                  {"000003BE6FDC"},
                  {"000098765432"}};

//Stucture for a cow distance
struct cow_dist{
  public:
  char CID[12];
  float d_cd = 0;
  //int t;
  //int valid = 0;
};

//Structure for a beacon that holds an array of 
//structures of distances to each cow
struct beacon_cows{
  public: 
  char BID_bc[13] = "123456789123";
  cow_dist cows[NumCows];
};

//Data Structures (Pretty sure they have to be declared here)
// Structure for location of a beacon
struct beacon_loc {
  public:   //lets me print the contents
  char BID[12] = "123456789123";
  float x, y, z;
};

beacon_loc bl_array[NumBeaks];

void loop() {
   beacon_cows beacon0;

   for (int i=0; i<12; i++){ //Assign all ones to bl_array of 3 then random values to the rest
    bl_array[0].BID[i] = b0id[i];
    bl_array[1].BID[i] = b1id[i];
    bl_array[2].BID[i] = b2id[i];
    bl_array[3].BID[i] = b3id[i]; 
    }
    
   for (int i = 0; i<12; i++){
      beacon0.BID_bc[i] = bl_array[0].BID[i]; //Set the BID in the beacon1 struct to the BID for our local B1 in the bl_array
      //Serial.print(bl_array[0].BID[i]);
      //beacon1.BID[i] = bl_array[1].BID[i];
      //beacon2.BID[i] = bl_array[2].BID[i];
      //beacon3.BID[i] = bl_array[3].BID[i];
  }
  //Serial.println();
  //print the BID for beacon1
  Serial.print("beacon0.BID = ");
  Serial.println(beacon0.BID_bc);
  delay(5000);
}
