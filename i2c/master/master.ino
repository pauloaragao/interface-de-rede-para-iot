#include "Wire.h"

// endereco do modulo slave que pode ser um valor de 0 a 255
#define slaveAdress 0x08

String myString = "";


void setup() {
  Serial.begin(115200);
  Wire.begin(); // ingressa ao barramento I2C
  
}

void loop() {
  Wire.requestFrom(slaveAdress, 4);    // request 6 bytes from slave device #8

   myString = "";                     // string para armazenar bytes enviados pelo slave
  while(Wire.available())    // slave may send less than requested
  {
    char c = Wire.read();    // receive a byte as character
    //Serial.print(c);         // print the character
    if ( c != NULL)
      myString += c;
  }

  delay(500);
  Serial.print(". Resposta do slave ==> ");
  Serial.print(myString);
  Serial.println("");
  delay(2000);

}
