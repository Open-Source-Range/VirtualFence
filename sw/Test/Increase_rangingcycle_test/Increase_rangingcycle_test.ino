char c;
/* List of IDs
  000009EEEE95
  00000RT93Y05
  000009FA68E3
  0000112A7CCA
  00002BB8DBE4 - Host
 */

 
 /* this code sets faster blinks 
*/
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  //Serial1.print("SBIV 60000\r\n");  //Set host to blink every 60000 ms
  //Serial1.print("NCFG 4\r\n");  // Set *RRN response to include minimum data
  //Serial1.print("SDAT 0 0000112A7CCA 0B 0812555402550003311388\r\n");   //Set cow to blink every 5000 ms
  //Serial1.print("SDAT 0 000009FA68E3 0B 0812555402550003317530\r\n");   //Set other remote node to blink every 60000 ms
}

void loop() {
  while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
  }
}
