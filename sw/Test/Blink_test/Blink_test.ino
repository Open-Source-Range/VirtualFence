void setup() {
  #include <stdio.h>
  #include <string.h>
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.print("NCFG 4\r\n");  // Set *RRN response to include RSSI data
  Serial1.print("SBIV 9000\r\n");  //Set host to blink every 10000 ms
  Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003312AF8\r\n");   //Set cow to blink every 11000 ms
  Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003312EE0\r\n");   //Set other remote node to blink every 12000 ms
  Serial1.print("SDAT 0 000009EEEE95 0B 08125554025500033132C8\r\n");   //13000 ms
}
//global variables
char IDblink[80] = {'\0'};  // IDblink (*RRN response) is 39 characters
int NumCows = 1;  //Will need to index the CowDistanceMatrix
float CowDistanceMatrix[1][4] = {55.17,51.225,86.28,48.42}; //Known distances, output should be around (40,38)
//float CowDistanceMatrix[1][4] = {39.4,56.86,102.728,44.4}; //Known distances, output should be around (32.2, 22.9);
//float CowDistanceMatrix[1][4];

void loop() {
  //Arrays for incoming data
  char ID1[] = "000000000002";
  char ID2[] = "000220022002";
  char d[] = "000000";
  char RSSI[4] = {'\0'};
  //Other Variables
  int track = 0;
  
  //Known Beacon ID's
  char b1[] = "000009EEEE95";
  char b2[] = "000009FA68E3";
  char b3[] = "00002BB8DBE4";
  char b4[] = "0000025DEE6B";
  int len = 0;
  int size = 0;
  
  //Known Cow IDs
  char cow[] = "0000112A7CCA";
  //char cow[][12] = {{"0000112A7CCA"},
                    //{"0000123456AS"},
                    //{"000098765432"}};
                    
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
        
        // Check that one ID is a cow
        if ((strcmp(ID1, cow) == 0)||(strcmp(ID2, cow) == 0)){
         //cow_distance(d, b1, b2, b3, b4, ID1, ID2, cow);   //Call function 
        }
        
        Serial.print("the cow matrix is: ");
        int checkmatrix=0;  //Variable to store how many non-zero distances are in the matrix
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
        
        if (checkmatrix>2){
          //trilateration();  //Call trilateration function if there are 3 or more distances
        }
      }
   
    }
  }
  
}
