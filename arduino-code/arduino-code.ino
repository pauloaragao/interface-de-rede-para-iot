#include "Wire.h"
#include <DHT.h>
#include <Thermistor.h>

#define myAdress 0x08 // endereco do modulo slave que pode ser um valor de 0 a 255

//Pino conectado ao pino de dados do sensor
#define DHTPIN 8
#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

// Analog pin used to read the NTC
#define NTC_PIN_0               A0
#define NTC_PIN_1               A1
#define NTC_PIN_2               A2
#define NTC_PIN_3               A3
#define NTC_PIN_4               A4


//Definicoes do sensor : pino, tipo
DHT dht(DHTPIN, DHTTYPE);

//Definicao do Termistor

Thermistor thermistor_0(NTC_PIN_0);
Thermistor thermistor_1(NTC_PIN_1);
Thermistor thermistor_2(NTC_PIN_2);
Thermistor thermistor_3(NTC_PIN_3);
Thermistor thermistor_4(NTC_PIN_4);

// Global temperature reading
float temp_0;
float temp_1;
float temp_2;
float temp_3;
float temp_4;

//String mensageira
String myString = "";

void setup() {
  Serial.begin(115200);
  dht.begin();
  Wire.begin(myAdress); // ingressa ao barramento I2C com o endereço definido no myAdress (0x08)
  Wire.onRequest(receiveEvent);  //Registra um evento para ser chamado quando chegar algum dado via I2C
}

void loop() {
  // nada para ser exexutado
    lerTemperatura();
    delay(2000);
}

// funcao executada sempre que algum dado e recebido no barramento I2C
// vide "void setup()"
void receiveEvent() {
  // verifica se existem dados para serem lidos no barramento I2C
  Wire.write(myString.c_str());
}

void lerTemperatura(){
  myString = "";
  //Leitura da umidade
  float h = dht.readHumidity();
  //Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  //Leitura Temperatura Placa Solar
  temp_0 = thermistor_0.getTemp();   // Read temperature
  temp_1 = thermistor_1.getTemp();   // Read temperature
  temp_2 = thermistor_2.getTemp();   // Read temperature
  temp_3 = thermistor_3.getTemp();   // Read temperature
  temp_4 = thermistor_4.getTemp();   // Read temperature
  
  myString = (String) h + ";" + (String) t + ";" + (String) temp_0 + ";" + (String) temp_1+ ";" + (String) temp_2+ ";" + (String) temp_3+ ";" + (String) temp_4;

  Serial.println(myString);
  return myString;
}
