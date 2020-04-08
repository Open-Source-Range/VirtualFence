void setup() {
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 4\r\n");  // Set *RRN response to include RSSI data
  Serial1.print("SBIV 60000\r\n");  //Set host to blink every minute
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003311388\r\n");   //Set cow to blink every 5000 ms (2710 IS 10)
  delay(2000);
  Serial1.print("SDAT 0 00002BB8D888 0B 081255540255000331EA60\r\n");   //Set cow to blink every 5000 ms
  Serial1.print("SDAT 0 000003BE6FDC 0B 081255540255000331EA60\r\n");   //Set other cow node to blink every 5000 ms
  Serial1.print("SDAT 0 00006888AFA6 0B 081255540255000331EA60\r\n");   //Set remote node to blink every minute
  delay(500);
  Serial1.print("SDAT 0 0000025DEE6B 0B 081255540255000331EA60\r\n");   //Set remote node to blink every minute
  Serial1.print("SDAT 0 000009EEEE95 0B 081255540255000331EA60\r\n");   //Set remote node to blink every minute
}

//global variables
char IDblink[80] = {'\0'};  // IDblink (*RRN response) is 39 characters
const int NumCows = 3;  //Will need to index the CowDistanceMatrix
const int NumBeaks = 4;
int start = 1;
int setup_beaks = 1;
int timeout = 0;
char my_ID[] = "111111111111";  //stores the ID for the host beacon
char b0id[] = "111111111111";  
char b1id[] = "0000025DEE6B";
char b2id[] = "000009EEEE95";
char b3id[] = "111111111111"; //Host Beacon

char cow[][13] = {{"0000112A7CCA"},
                  {"000009FA68E3"},
                  {"000098765432"}};
                  
//float CowDistanceMatrix[4] = {55.17,51.225,86.28,48.42}; //Known distances, output should be around (40,38)
//float CowDistanceMatrix[4] = {39.4,56.86,102.728,44.4}; //Known distances, output should be around (32.2, 22.9);
float CowDistanceMatrix[NumCows][NumBeaks];
int count_dist[NumCows];


//Data Structures (Pretty sure they have to be declared here)
// Structure for location of a beacon
struct beacon_loc {
  public:   //lets me print the contents
  char BID[13] = "123456789123";
  float x, y, z;
};

//Stucture for a cow distance
struct cow_dist{
  public:
  char CID[12];
  float d_cd = 0;
  unsigned long t = 0;
  //int valid = 0;
};

//Structure for a cow location
struct cow_loc{
  public:
  char  CID[12];
  float x, y, z;
  int valid = 0;
};

//Structure for a beacon that holds an array of 
//structures of distances to each cow
struct beacon_cows{
  public: 
  char BID_bc[13] = "123456789123";
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

//Array of 4 beacon_cows
//One for each of the 4 local beacons
beacon_cows beacon_array[4];


void loop() {
  //This code calls the get_my_id() function 
  //It only works when you pre set a my_ID string and have the function override it, probably fine??
  if(start){
    get_my_id();
    if(timeout < 4){
      get_my_id();
    }
    set_structs();  //call function to set cow and beacon IDs
    start = 0;
  }


  //*****THIS IS THE CODE WE ALREADY HAD FOR PARSING, ETC.****
  //Arrays for incoming data
  char ID1[] = "000000000002";
  char ID2[] = "000220022002";
  char d[] = "000000";
  char RSSI[4] = {'\0'};
 
  //Other Variables
  int track = 0;
  int len = 0;
  int size = 0;
  
  //Known Cow IDs
                    
  //Read asynchronous input from host
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
        
        for (int i = 2; i < 80; i++) {
          while (!Serial1.available()) {
          //Wait for a Response
          }
          c = Serial1.read();               //Keep Reading in Node ID 
          if (c=='*'){
            bad = 1;  //variable to check for overlapping *RRN commands
            break;
          } 
        
          //stop filling out IDBlink at new line - not needed
          if (c=='\n') {
            IDblink[i]=c;
            track=i;
            //Serial.println(track);  //print length of serial command
            break;                          
          }
        
          IDblink[i] = c;
        }
      
        if (bad==1) {    //Exit while loop if overlapping *RRN commands
          Serial.println("overlap");
          continue;
        }

        Serial.println();
        Serial.print(IDblink);
    
        //Seperates and Saves IDblink into Components and prints each component one char at a time
        //First Node ID
  
        
        for (int i = 0; i < 12; i++) {
          ID1[i] = IDblink[i + 5];
        }
        Serial.print("ID1 = ");
        Serial.println(ID1);
  
        //Second Node ID
        for (int i = 0; i < 12; i++) {
          ID2[i] = IDblink[i + 18];
        }
        Serial.print("ID2 = ");
        Serial.println(ID2);
        
        //Distance value in cm
        for (int i = 0; i < 6; i++) {
          d[i] = IDblink[i + 33];
       }
  
       Serial.print("distance = ");
       Serial.print(d);
       Serial.println(" centimeters");
       
       //RSSI Value
       for (int i=0; i<3; i++){
        if (IDblink[i+45]=='\n'){
          continue;
        }
        RSSI[i]=IDblink[i+45];
        }
  
        Serial.print("RSSI = ");
        Serial.println(RSSI);
        

        //Fill IDblink with null chars
        IDblink[80] = {'\0'};
        
        char fakecow[] = "123456789123";
        
        for (int i = 0; i<NumCows; i++){
          // fill fakecow variable because can't compare with the cow for some reason
          for (int j=0; j<12; j++){
            fakecow[j] = cow[i][j];
          }
          
          for (int k = 0; k<NumBeaks; k++){
            
            //Only call cow distance function if ID1 is a beacon, ID2 is a cow and there is no signal error
            //when there is a question mark, the RSSI string is "?\r"
            //Then call the function and pass which cow (i) and which beacon (k)
            if ((((strcmp(ID1, beacon_array[k].BID_bc) == 0)&&(strcmp(ID2, fakecow) == 0))||((strcmp(ID2, beacon_array[k].BID_bc) == 0)&&(strcmp(ID1, fakecow) == 0)))&&(strcmp(RSSI,"?\r")!=0)){
              Serial.print("this is cow: ");
              Serial.println(i);
              Serial.print("this is beacon: ");
              Serial.println(k);
              cow_distance(d, ID1, ID2, i, k, fakecow);   //Call function to calculate distance
              //send which cow and which beacon
             }
          }
        }
        Serial.println();

        time_check(); //call function to check if distances are still valid
        
      for (int i = 0; i < NumCows; i++){
        count_dist[i] = 0;  //reset count_dist tracker each loop
      }
        int which_cow=0;
        //Loop through all cows and all beacons
        for(int i = 0; i< NumCows; i++){
          for(int j =0; j<4; j++){
            if (beacon_array[j].cows[i].d_cd > 0.00){
              count_dist[i]++;          //if the distance is greater than 0 for a cow, increment count_dist for that cow
              if (count_dist[i] > 2){   //if there are 3 valid distances
                  which_cow = i;        //set a variable to mark which cow has 3 valid distances
                  count_dist[i] = 0;    //reset count variable for that
                  trilateration(which_cow);   //call trilateration function
              }
            }
          }
        }


       /*
        //Old code for one cow
        Serial.print("the cow matrix is: ");
        int checkmatrix=0;  //Variable to store how many non-zero distances are in the matrix
        for (int i=0; i<4;i++){
          Serial.print(CowDistanceMatrix[i]);
          Serial.print(" ");
          if (CowDistanceMatrix[i]!=0.00){
            checkmatrix=checkmatrix+1;
          }
        }
        Serial.println();
        Serial.print("the matrix is this full: ");
        Serial.println(checkmatrix);
        
        if (checkmatrix>2){
          //trilateration();  //Call trilateration function if there are 3 or more distances
        }
        */
      }
   
    }
  }
  
}
