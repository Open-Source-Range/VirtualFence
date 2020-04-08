char c;
/* List of IDs
  000009EEEE95
  100009FA68E3
  00000RT93Y05
  000009FA68E3
  0000112A7CCA
 */
 /* Example Code for host device
  Serial1.print("GPIO 1 1 0 0 2\r\n");  // configure GPIO[1] as output with pulldown
  delay(20);
  Serial1.print("GPIO 2 1 0 0 2\r\n");  // configure GPIO[2] as output with pulldown
  delay(20);
  Serial1.print("GPIO 3 1 0 0 2\r\n");  // configure GPIO[3] as output with pulldown
  delay(20);
  Serial1.print("SPIN 0F 01\r\n");      // set GPIO 0-3 to high
  delay(50);
  Serial1.print("SPIN 06 00\r\n");    // set GPIO 1,2 low
  delay(50);
  Serial1.print("SPIN 06 01\r\n");    // set GPIO 1,2 high
*/
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  /*
  Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0101000002\r\n");
  delay(1000);
  Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0201000002\r\n");
  delay(1000);
  Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0301000002\r\n");
  delay(1000);
   Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0001000002\r\n");
  delay(1000);
  //Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0101\r\n");
  //delay(1000);
  */
}

void loop() {
  Serial1.print("SDAT 1 0000112A7CCA 0B 0812555402550003232710 60000\r\n"); //SSTART command to force receiver active for 60 seconds
  delay(100);
  Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0101000002\r\n"); //Configure GPIO[1] as output with pulldown
  delay(100);
  //Serial1.print("SDAT 0 0000112A7CCA 09 081255540255000124\r\n"); //SEXTEND command to force receiver active longer
  //delay(100);
  
  while(1) {
    while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
      }
      Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0101\r\n"); //Set pin 1 on remote device high
      delay(350);
      Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0100\r\n"); //Set pin 1 on remote device low
      delay(350);
      
  }
  
}
