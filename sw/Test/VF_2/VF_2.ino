#include <string.h>

//Known Beacon ID's
  char b1[14] = "000009EEEE95";
  char b2[14] = "000009FA68E3";
  char b3[14] = "00000RT93Y05";
  char b4[14] = "100009FA68E3";

//Known Cow ID's
  char cow[14] = "0000112A7CCA";

//Distance Variables (char type)
  char db1[6] = "000000";
  char db2[6] = "000000";
  char db3[6] = "000000";

//Distance Variables (int type)
  int db1i, db2i, db3i;

//Extracted ID's and current distance from IDblink
  char ID1[14];
  char ID2[14];
  char d[7];

//IDblink Variables
  char IDblink[39];

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  IDBlink();
}
