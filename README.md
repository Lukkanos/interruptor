# interruptor Inteligente
Título: Interruptor Inteligente com ESP01 e Arduino

## Descrição:
Este projeto visa criar um interruptor inteligente que possa ser controlado remotamente utilizando tecnologia Wi-Fi. O projeto utiliza um módulo ESP01 para conexão Wi-Fi e um Arduino para controle do interruptor.

## Funcionalidades:

- Controle remoto do interruptor via Wi-Fi ultilizando um módulo ESP01 para conexão Wi-Fi para controle do interruptor.

## Materiais e Liguagem Utilizadas:

- 1	Arduino Uno R3
- 1	Módulo Wifi (ESP8266)
- 2	1 kΩ Resistor
- 1	LED Vermelho 
- 1	10 kΩ Resistor
- 1	150 Ω Resistor
- Linguagem de programação: C++

## Conexão Arduino e ESP01:

Arduino          ESP-01
3.3V ----------→ VCC
GND ----------→  GND
Pin 2 (RX - Arduino) → TX (ESP)
Pin 3 (TX - Arduino) → RX (ESP) via divisor
3.3V ----------→ CH_PD (ou EN)

Pino 9 (PWM) → (LED embutido)

## Autores:
Eloisa
Luana Fernanda Scchor
Lucas Ariel Soares Caetano
