/********************************************************
 * TCC PAULO - INTERFACE DE REDE MONITORAMENTO DE REDE
 * ESP32 - Utilizando MQTT
 * 07/2021 - @pauloaragaoo
 * Historico
 */
int i;
String t, h;


// Bibliotecas ------------------------------------------
  //Biblioteca de Sensores
  #include "DHT.h"
  #include "PubSubClient.h" // Conecta ao MQTT Broker
  #include "WiFi.h" // Permite que o ESP32 se conecte à rede local (via WiFi)
  #include <WiFiClientSecure.h> //Conexão segura ao broker
  #include "WebServer.h" //Servidor http do ESP32
  #include "HTTPClient.h"
  #include "Wire.h"

// Wi-Fi ------------------------------------------------
  const char* ssid = "YepNET Cavalo de Troia";                
  const char* wifi_password = "P@ulo3034605"; 

// Constantes -------------------------------------------
  // DHT22
    #define DHTPIN 4  // Pino conectado ao sensor DHT
  // Endereco do Slave I2C
    #define slaveAdress 0x08
  // Broker
    //const char* mqtt_server = "192.168.3.20";
     const char* mqtt_server = "177.223.134.56";
  // Porta
    //const int mqtt_port = 8883;
    const int mqtt_port = 65002; 
  // Cliente
    const char* mqtt_username = "zeus"; 
  // Secret MQTT
    const char* mqtt_password = "paulo3034605";
  // Cliente
    const char* clientID = "client_livingroom"; 
  /*// Topico Livingroom Humidity
    const char* humidity_topic = "home/livingroom/humidity";
  // Topico Livingroom Temperature
    const char* temperature_topic = "home/livingroom/temperature";
  */
   // Topico Umidade no Local
    const char* umidadelocal_topic = "placasolar/zeus/umidadelocal";
  // Topico Temperatura Local
    const char* temperaturalocal_topic = "placasolar/zeus/temperaturalocal";
  // Topico Temperatura Placa Solar 01
    const char* temperatura_01_topic = "placasolar/zeus/temperatura_01";
  // Topico Temperatura Placa Solar 02
    const char* temperatura_02_topic = "placasolar/zeus/temperatura_02";
  // Topico Temperatura Placa Solar 03
    const char* temperatura_03_topic = "placasolar/zeus/temperatura_03";
  // Topico Temperatura Placa Solar 04
    const char* temperatura_04_topic = "placasolar/zeus/temperatura_04";
  // Topico Temperatura Placa Solar 05
   const char* temperatura_05_topic = "placasolar/zeus/temperatura_05";
    

// Variaveis globais ------------------------------------
  String myString;

// Temporario para teste ------------------------------------
  #define DHTTYPE DHT22  // DHT11 or DHT22
  DHT dht(DHTPIN, DHTTYPE);


// Instancias -------------------------------------------
  WiFiClient wifiClient;
  //WiFiClientSecure wifiClient;
  PubSubClient client(mqtt_server ,1883, wifiClient); 
  //PubSubClient client(mqtt_server, mqtt_port, wifiClient);

// Funcoes Genericas ------------------------------------
void connect_MQTT(){
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
    connect_MQTT();
  }
}

void wificonnect(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  Wire.begin(); // ingressa ao barramento I2C
  wificonnect();
  
  dht.begin();
 
}

void loop() {
  connect_MQTT();

  Serial.setTimeout(2000);
  solicitandoSlave();
  //separarString();
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  //Serial.print(myString);
  
  /*Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");*/

  int tEntrada = myString.length();
  char separator[] = ";";
  Serial.print("Tamanho Entrada: ");
  Serial.println(tEntrada);

  char char_array[tEntrada + 1];

  // copying the contents of the 
  // string to char array 
  strcpy(char_array, myString.c_str());
  char *token = NULL;
  token = strtok(char_array, separator);
  
  //Serial.print("Token: ");
  //Serial.println(token);

  // Find any more?
   while(token != NULL)
   { 
     h = token;
     String hs="Hum: "+String(token)+" % ";
     Serial.println(hs);
     token = strtok(NULL, separator);
     t = token;
     String ts="Temp: "+String(token)+" C ";
     Serial.println(ts);
     token = strtok(NULL, separator);
      
   } 



  // MQTT can only transmit strings
  //String hs="Hum: "+String((float)h)+" % ";
  //String ts="Temp: "+String((float)t)+" C ";

  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
  if (client.publish(temperaturalocal_topic, String(t).c_str())) {
    Serial.println("Temperature sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(temperaturalocal_topic, String(t).c_str());
  }

  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  if (client.publish(umidadelocal_topic, String(h).c_str())) {
    Serial.println("Humidity sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Humidity failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(umidadelocal_topic, String(h).c_str());
  }
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*30);       // print new values every 1 Minute
}

void solicitandoSlave(){
  Wire.requestFrom(slaveAdress, 11);    // request 6 bytes from slave device #8

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
/*
void separarString(){
  int i = 0;
  int tEntrada = myString.length();
  char separator[] = ";";
  Serial.print("Tamanho Entrada: ");
  Serial.println(tEntrada);

  char char_array[tEntrada + 1];

  // copying the contents of the 
  // string to char array 
  strcpy(char_array, myString.c_str());
  char *token;
  token = strtok(char_array, separator);

  //Serial.print("Token: ");
  //Serial.println(token);

  // Find any more?
   while(token != NULL)
   {  
     token = strtok(NULL, separator);
     Serial.print("Token quebrado: ");
     Serial.println(token);
     if ( i == 0 ){
      h = float(token);
      i = 1;
     }
     if ( i == 1 ){
      t = float(token);
      i = 2;
     }
     if (i == 2){
      i = 0
     }
   } 
}*/
