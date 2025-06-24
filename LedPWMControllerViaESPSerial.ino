#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); 

const int ledPin = 9; // Pino PWM para controlar o Brilho do LED
int brilho = 255;
bool ligado = false;

void setup() {
  Serial.begin(9600);      
  espSerial.begin(9600);   
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);  
}

void loop() {
  if (espSerial.available()) {
    String comando = espSerial.readStringUntil('\n');
    comando.trim();
    Serial.print("Recebido do ESP: ");
    Serial.println(comando);

    if (comando == "LIGAR") {
      ligado = true;
      analogWrite(ledPin, brilho);
    } else if (comando == "DESLIGAR") {
      ligado = false;
      analogWrite(ledPin, 0);
    } else if (comando.startsWith("BRILHO:")) {
      int val = comando.substring(7).toInt();
      brilho = map(val, 0, 100, 0, 255);
      if (ligado) {
        analogWrite(ledPin, brilho);
      }
    }
  }
}
