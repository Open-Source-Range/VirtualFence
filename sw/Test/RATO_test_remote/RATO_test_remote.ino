char c;
/* List of IDs
  000009EEEE95
  100009FA68E3
  00000RT93Y05
  000009FA68E3
  0000112A7CCA
  00002BB8DBE4 - Host
 */

 
 /* Example Code for host device
  Serial1.print("RATO 0 0000112A7CCA\r\n"); //Initiates a ranging cycle immediately to the cow ID from the host
*/
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

// The first section initiates ranging cycles immediately from the host device with the cow and another node 
void loop() {
  /*
  delay(4000);
  Serial1.print("RATO 0 0000112A7CCA\r\n");
  while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
  }
  delay(4000);
  Serial1.print("RATO 0 000009FA68E3\r\n");
  while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
  }
  */
  
// Now this code uses SDAT to get distance between the two remote nodes
  Serial1.print("SDAT 1 0000112A7CCA 0B 0812555402550003232710 60000\r\n"); //SSTART command to force receiver active for 60 seconds
  while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
  }
  delay(500);
  Serial1.print("SDAT 0 0000112A7CCA 0F 081255540255000712000009FA68E3\r\n"); //Send SDAT command to cow with RATO command to get ranging distance to other remote node
  while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
  }
  delay(2000);
  
}
