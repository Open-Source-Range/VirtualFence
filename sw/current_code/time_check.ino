void time_check(){
  //Function to check how long the distances have been there
  unsigned long timenow;
  for (int i = 0; i < NumCows; i++){
    for (int j = 0; j < 4; j++){
      timenow = millis();
      //if they have been there for over 120 seconds, the distance resets to 0
      //time also resets
      if ( timenow - beacon_array[j].cows[i].t > 120000 ){
        beacon_array[j].cows[i].d_cd = 0.00;
        beacon_array[j].cows[i].t = 0.0;
      }
    }
    
  }
}
