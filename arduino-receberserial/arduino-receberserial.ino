// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

String data = "";

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}


void loop() {
  Wire.requestFrom(0x08, 12);    // request 6 bytes from slave device #8

   //Wire.beginTransmission(0x08);
  data = "";                     // string para armazenar bytes enviados pelo slave
  while( Wire.available()){
    data += (String)Wire.read();
  }
  Serial.print(". Resposta do slave ==> ");
  Serial.print(data);
  Serial.println("(FIM)");
  Serial.println("");



  //Wire.endTransmission(0x08);
  /*while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
  }
  Serial.println(c);         // print the character*/
  delay(4000);
}
