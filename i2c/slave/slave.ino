#include "Wire.h"


#define myAdress 0x08 // endereco do modulo slave que pode ser um valor de 0 a 255

String myString = "";

void setup() {
  Serial.begin(115200);
  Wire.begin(myAdress); // ingressa ao barramento I2C com o endereço definido no myAdress (0x08)
 
  Wire.onRequest(receiveEvent);  //Registra um evento para ser chamado quando chegar algum dado via I2C

}

void loop() {
  // nada para ser exexutado
}

// funcao executada sempre que algum dado e recebido no barramento I2C
// vide "void setup()"
void receiveEvent() {
  // verifica se existem dados para serem lidos no barramento I2C
  Wire.write("1020");
}
