void set_structs(){
  // Set the BIDs in the bl_array to the known 4 beacon Ids
  for (int i=0; i<12; i++){ 
    bl_array[0].BID[i] = b0id[i];
    bl_array[1].BID[i] = b1id[i];
    bl_array[2].BID[i] = b2id[i];
    bl_array[3].BID[i] = b3id[i]; 
    }

  //print the bl_array
  Serial.println("bl_array is: ");
  for (int k = 0; k<4; k++){
    Serial.println(bl_array[k].BID);
  }
  Serial.println();
  //Now code to set the BID in each of these to the correct BID:
  for (int i = 0; i<12; i++){
    beacon_array[0].BID_bc[i] = bl_array[0].BID[i]; 
    beacon_array[1].BID_bc[i] = bl_array[1].BID[i]; 
    beacon_array[2].BID_bc[i] = bl_array[2].BID[i]; 
    beacon_array[3].BID_bc[i] = bl_array[3].BID[i]; 
    //beacon0.BID_bc[i] = bl_array[0].BID[i]; //Set the BID in the beacon1 struct to the BID for our local B1 in the bl_array
    //beacon1.BID_bc[i] = bl_array[1].BID[i];
    //beacon2.BID_bc[i] = bl_array[2].BID[i];
    //beacon3.BID_bc[i] = bl_array[3].BID[i];
  }
  /*
  //print the BID for beacon1
  Serial.println("beacon.BIDs are ");
  for (int i = 0; i<4; i++){
    Serial.println(beacon_array[i].BID_bc);
  }
  */
  
  //Set the list of cow IDs for each beacon_cows Struct
  for (int i = 0; i<NumCows; i++){
    for (int j = 0; j<12; j++){
      beacon_array[0].cows[i].CID[j] = cow[i][j];
      beacon_array[1].cows[i].CID[j] = cow[i][j];
      beacon_array[2].cows[i].CID[j] = cow[i][j];
      beacon_array[3].cows[i].CID[j] = cow[i][j];
    }
  }

  //Print the CIDs for one beacon
  Serial.println("CID array for each beacon is: ");
  for(int i = 0; i<NumCows; i++){
    Serial.println(beacon_array[1].cows[i].CID);
  }
}
