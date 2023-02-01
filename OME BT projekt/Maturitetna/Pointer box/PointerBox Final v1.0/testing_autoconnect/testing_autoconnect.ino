#include "RN42BT.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

RN42BT Bluetooth;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);
  //mySerial.println("Hello, world?");
    digitalWrite(6, HIGH); //red light
    digitalWrite(5, HIGH);
    delay(500);
    mySerial.write(BP_MODE_COMMAND);
    delay(50);
    mySerial.write(BP_CONNENT);
    
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
