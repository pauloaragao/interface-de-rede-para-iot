// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <DHT.h>

//Pino conectado ao pino de dados do sensor
#define DHTPIN 8
#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

//Definicoes do sensor : pino, tipo
DHT dht(DHTPIN, DHTTYPE);

String data = "";

void setup() {
  Serial.begin(9600);
  Wire.begin(0x08);                // join i2c bus with address #8
    Wire.onRequest(receiveEvent); // register event
  //Wire.onRequest(requestEvent); // register event
  //Iniclaiza o sensor DHT
  dht.begin();
}

void loop() {
  
  
  delay(2000);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
//void requestEvent() {
  void receiveEvent(){
  data = "";
  //Leitura da umidade
  float h = dht.readHumidity();
  //Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  data = String(h) + ';' + String(t) + '.';
  char* buf = (char*) malloc(sizeof(char)*data.length()+1);

  Serial.println(data);
  //Wire.write(data.c_str());

  data.toCharArray(buf, data.length()+1);
  Serial.print("Buf:");
  Serial.println(buf);
  Wire.write(buf);
  free(buf);
  //Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
