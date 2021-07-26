# Interface de Rede para Soluções IoT
A solução proposta nesse projeto é que para qualquer solução via microcontrolador compatível com I2C possa ser transmitido via MQTT para um repositório remoto e apresentado via Grafana. Para melhor implementação foi implementado a solução do Servidor até o microcontrolador. 

<img src="/docs/diagramadeblocos-geral.png"/>

* Servidor: Raspberry 3 B+;
* Interface de Rede: ESP32 DEV KIT v1;
* Coletor de Sensor: Arduíno Uno;
* Sensor: DHT22

## Configuração do Servidor
Para configuração do servidor pode-se olhar o wiki o passo a passo do mesmo: https://github.com/pauloaragao/interface-de-rede-para-iot.wiki.git
<img src="/docs/diagramadeblocos-servidor.png"/>

## Estutura da Interface de Rede
<img src="/docs/estruturadecomunicacao.png"/>

