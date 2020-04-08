void get_my_id(){
  char myID[80];
  int i = 0;
  int j;
  int leave = 0;
  int tstart = millis();
  Serial1.print("SNID 000000000000\r\n");
  int done = 0;
  
  while(!done){
    
   // while (Serial1.available() && (done == 0)) {
      while (Serial1.available()) {
        myID[i] = Serial1.read();
        
        if(myID[i] == '\n'){  //A full command is finished if a new line is read in
          done = 1;
          //Serial.println("DONE IS 1!");
          //Serial.println(myID);
          delay(10);
        }      
        i++;    
    }
    
    if( (millis() - tstart) > 100){ //If it takes too long, exit out and try again
      Serial.println("Timeout");
      timeout++;
      leave = 1;
      break;
    }
    
    if(leave){
      break;
    }
    
    if(done == 1){  //if there was a new line check if the command doesn't start with = 
      //or if it is not 14 chars long
      if ( !( (myID[0] == '=') && (i == 15) ) ) {
        done = 0; //restart
        i = 0;
        myID[80] = {'\0'};  //reset the myID array
      }
      else{   //if it does start with = and is the correct length
        for(j = 0; j<12; j++){
          my_ID[j] = myID[j+1]; //set the global my_ID variable
        }
        Serial.print("My ID final: ");
        Serial.println(my_ID);
        Serial.println();
        for(int i = 0; i<12; i++){
            b0id[i]=my_ID[i];
        }
      }
    }
  }

  //myID[0] = '0';
  //int myIDint = atol(myID);
  //Serial.print("My ID = ");
  //for (j=0;j<i;j++) {
  //Serial.print(myID[j]);
  //}

  
  
}
