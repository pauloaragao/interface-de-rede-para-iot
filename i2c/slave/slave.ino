#include "Wire.h"
#include <DHT.h>

#define myAdress 0x08 // endereco do modulo slave que pode ser um valor de 0 a 255

//Pino conectado ao pino de dados do sensor
#define DHTPIN 8
#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

//Definicoes do sensor : pino, tipo
DHT dht(DHTPIN, DHTTYPE);


String myString = "";

void setup() {
  Serial.begin(115200);
  dht.begin();
  Wire.begin(myAdress); // ingressa ao barramento I2C com o endereço definido no myAdress (0x08)
  Wire.onRequest(receiveEvent);  //Registra um evento para ser chamado quando chegar algum dado via I2C
}

void loop() {
  // nada para ser exexutado
    lerDHT();
    delay(2000);
}

// funcao executada sempre que algum dado e recebido no barramento I2C
// vide "void setup()"
void receiveEvent() {
  // verifica se existem dados para serem lidos no barramento I2C
  Wire.write(myString.c_str());
}

void lerDHT(){
  myString = "";
  //Leitura da umidade
  float h = dht.readHumidity();
  //Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  myString = (String) h + ";" + (String) t + "@";

  Serial.println(myString);
  return myString;
}
