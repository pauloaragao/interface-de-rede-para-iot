/********************************************************
 * TCC PAULO - INTERFACE DE REDE MONITORAMENTO DE REDE
 * ESP32 - Utilizando MQTT
 * 07/2021 - @pauloaragaoo
 * Historico
 */
int i = 0;
float t = 20;
float h = 80;


// Bibliotecas ------------------------------------------
  //Biblioteca de Sensores
  #include "DHT.h"
  #include "PubSubClient.h" // Conecta ao MQTT Broker
  #include "WiFi.h" // Permite que o ESP32 se conecte à rede local (via WiFi)
  #include <WiFiClientSecure.h> //Conexão segura ao broker
  #include "WebServer.h" //Servidor http do ESP32
  #include "HTTPClient.h"
  //#include "TimeLib.h"

// Wi-Fi ------------------------------------------------
  const char* ssid = "YepNET Cavalo de Troia";                
  const char* wifi_password = "P@ulo3034605"; 

// Constantes -------------------------------------------
  // DHT22
    #define DHTPIN 4  // Pino conectado ao sensor DHT
  // Broker
    const char* mqtt_server = "192.168.3.20";  
  // Porta
    const int mqtt_port = 8883; 
  // Cliente
    const char* mqtt_username = "zeus"; 
  // Secret MQTT
    const char* mqtt_password = "paulo3034605";
  // Topico Livingroom Humidity
    const char* humidity_topic = "home/livingroom/humidity";
  // Cliente
    const char* clientID = "client_livingroom"; 
  // Topico Livingroom Temperature
    const char* temperature_topic = "home/livingroom/temperature";


// Variaveis globais ------------------------------------


// Temporario para teste ------------------------------------
  #define DHTTYPE DHT22  // DHT11 or DHT22
  DHT dht(DHTPIN, DHTTYPE);


// Instancias -------------------------------------------
  WiFiClient wifiClient;
  //WiFiClientSecure wifiClient;
  PubSubClient client(mqtt_server, 1883, wifiClient); 
  //PubSubClient client(mqtt_server, mqtt_port, wifiClient);

// Funcoes Genericas ------------------------------------
void connect_MQTT(){
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

  
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  Serial.print("clientID: ");
  Serial.println(clientID);
  Serial.print("mqtt_username: ");
  Serial.println(mqtt_username);
  Serial.print("mqtt_password: ");
  Serial.println(mqtt_password);
  
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}


void setup() {
  Serial.begin(9600);
  dht.begin();
 
}

void loop() {
  connect_MQTT();

  Serial.setTimeout(2000);
  
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  h = h + 0.01;
  t = t + 0.01;

  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");


  // MQTT can only transmit strings
  String hs="Hum: "+String((float)h)+" % ";
  String ts="Temp: "+String((float)t)+" C ";

  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
  if (client.publish(temperature_topic, String(t).c_str())) {
    Serial.println("Temperature sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(temperature_topic, String(t).c_str());
  }

  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  if (client.publish(humidity_topic, String(h).c_str())) {
    Serial.println("Humidity sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Humidity failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(humidity_topic, String(h).c_str());
  }
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000*30);       // print new values every 1 Minute
}
