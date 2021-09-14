//Fonte: Fórum www.labdegaragem.com

#define pinterm A0 //Pino onde o termistor está ligado 
#define termres 10000 //Valor do termistor, no caso estamos utilizando um termistor de 10k 
#define tempnominal 25 //Temperatura nominal do ntc utilizado, esse dado deve ser pesquisado no datasheet
//do ntc que você está utilizando 
#define numsamples 5 //Número de amostras
#define beta 3977 //Valor do beta, esse valor varia conforme ntc, você deve verificar o datasheet
#define res 10000

int amostra[numsamples];
int i; 
void setup(void) {
Serial.begin(9600);
analogReference(EXTERNAL);
}

void loop(void) {
float media;

for (i=0; i< numsamples; i++) {
amostra[i] = analogRead(pinterm);
delay(10);
}

media = 0;
//quantidade de amostras
for (i=0; i< numsamples; i++) {
media += amostra[i];
}
media /= numsamples;
// conversão do valor de tensão em resistência
media = 1023 / media - 1;
media = res / media;

//Faz o cálculo pela fórmula do Fator Beta
float temperatura;
temperatura = media / termres; // (R/Ro)
temperatura = log(temperatura); // ln(R/Ro)
temperatura /= beta; // 1/B * ln(R/Ro)
temperatura += 1.0 / (tempnominal + 273.15); // + (1/To)
temperatura = 1.0 / temperatura; // Inverte o valor
temperatura -= 273.15; // Converte para Celsius

Serial.print("Temperatura: "); 
Serial.print(temperatura);
Serial.println(" °C");

delay(1000);
}
