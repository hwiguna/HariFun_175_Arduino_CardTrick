/*This program uses the updated SoftwareSerial distributed in v1.0 of 
the Arduino software. Users of earlier versions must download 
NewSoftSerial. */

#include <SoftwareSerial.h>

#define rxPin 255       // Not used, so set to invalid pin #
#define txPin 3         // Connect BPI/BPK's SER input to this pin.
#define inverted 1     // In setup, 1=inverted, 0=noninverted

const char clearScreen[ ] = {
  254,1,254,128,0};
const char message[ ] = "Hello World!" ;

/* 
Set up a new serial output using the pin definitions above. Note the 
argument "inverted," which instructs SoftwareSerial to output BPI/BPK-
compatible inverted-TTL serial (like RS-232, but without the +/- 
voltage swing).*/

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin, inverted);

void setup()  {
  // define pin mode for tx:
  digitalWrite(txPin, LOW);   // Stop bit state for inverted serial
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);    // Set the data rate
  delay(10);              // wait (may not be needed w/ Arduino v1.0)
  
  //mySerial.print(message);  
  
}

void loop() {
  int val = analogRead(A0);
  mySerial.print(clearScreen);
  mySerial.print("v=");
  mySerial.print(val);
  delay(1000);
}
