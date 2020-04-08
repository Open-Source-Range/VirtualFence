char c;

/* List of IDs
  000009EEEE95
  100009FA68E3
  00000RT93Y05
  000009FA68E3
  0000112A7CCA
 */

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
 
  
}

void loop() {
  Serial1.print("GPIO 0 1 0 0 2\r\n");  // configure GPIO[0] as output with pulldown
  delay(20);
  Serial1.print("GPIO 1 1 0 0 2\r\n");  // configure GPIO[1] as output with pulldown
  delay(20);
  Serial1.print("GPIO 2 1 0 0 2\r\n");  // configure GPIO[2] as output with pulldown
  delay(20);
  Serial1.print("GPIO 3 1 0 0 2\r\n");  // configure GPIO[3] as output with pulldown
  delay(20);
  Serial1.print("SPIN 0F 01\r\n");      // set GPIO 0-3 to high

  while (1) {
    while (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
      }
    delay(50);
    Serial1.print("SPIN 06 00\r\n");    // set GPIO 1,2 low
    delay(50);
    Serial1.print("SPIN 06 01\r\n");    // set GPIO 1,2 high
  }
}
