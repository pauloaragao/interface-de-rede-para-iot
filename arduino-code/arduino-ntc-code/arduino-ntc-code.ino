#include <Thermistor.h>

String myString = "";

// Analog pin used to read the NTC
#define NTC_PIN_0               A0
#define NTC_PIN_1               A1
#define NTC_PIN_2               A2
#define NTC_PIN_3               A3
#define NTC_PIN_4               A4

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

void lerNTC(){
  myString = "";
  temp_0 = thermistor_0.getTemp();   // Read temperature
  temp_1 = thermistor_1.getTemp();   // Read temperature
  temp_2 = thermistor_2.getTemp();   // Read temperature
  temp_3 = thermistor_3.getTemp();   // Read temperature
  temp_4 = thermistor_4.getTemp();   // Read temperature

  myString = (String) temp_0 + ";" + (String) temp_1+ ";" + (String) temp_2+ ";" + (String) temp_3+ ";" + (String) temp_4;
  Serial.println(myString);
  return myString;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  lerNTC();
  /*Serial.print("Temp_0: ");
  Serial.print(temp_0);
  Serial.print(" Temp_1: ");
  Serial.print(temp_1);
  Serial.print(" Temp_2: ");
  Serial.print(temp_2);
  Serial.print(" Temp_3: ");
  Serial.print(temp_3);
  Serial.print(" Temp_4: ");
  Serial.println(temp_4);
  */
  delay(1000);
}
