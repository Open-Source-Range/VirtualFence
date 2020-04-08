void search_bl_array(){
  //Function to search the bl_array for bl_array[i].BID = my_ID[]
  //Then sets mybeaks[0]=i 
  Serial.println("hi from function");
  int index;
  int found = 0;  //to make sure beacon was found
  for (int i=0; i<NumBeaks; i++){
    if (strcmp(bl_array[i].BID, my_ID)==0){
      index =  i;
      found = 1;
      Serial.print("i in function = ");
      Serial.println(i);
      continue;
    }
  }
  if(!found) {
    Serial.println("Did not find my_ID in bl_array");
  }
  my_beaks[0]=index;
  
}
