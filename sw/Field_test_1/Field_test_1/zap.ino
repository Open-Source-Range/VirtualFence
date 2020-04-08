void zap(float Xf, float Yf){
  //Set LED based on a location
  if (Xf>30.0||Yf>30.0){
    Serial1.print("SDAT 1 0000112A7CCA 0B 0812555402550003232710 60000\r\n"); //SSTART command to force receiver active for 60 seconds
    delay(100);
    Serial1.print("SDAT 0 0000112A7CCA 0E 08125554025500065a0101000002\r\n"); //Configure GPIO[1] as output with pulldown
    delay(100);
    Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0101\r\n"); //Set pin 1 on remote device high for one second
    Serial.println("ZAP");
    delay(3000);
    Serial1.print("SDAT 0 0000112A7CCA 0B 08125554025500035b0100\r\n"); //Set pin 1 on remote device low
  }
}
