#include <SoftwareSerial.h>

// Pines del Bluetooth en el control (RX, TX)
SoftwareSerial BTSerial(10, 11);

// Pines del Joystick
const int pinX = A0;
const int pinY = A2;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  int valorX = analogRead(pinX); // Izquierda (~0) a Derecha (~1023)
  int valorY = analogRead(pinY); // Arriba (~0) a Abajo (~1023)

  // Mover hacia adelante (Palanca hacia arriba)
  if (valorY < 300) {
    BTSerial.write('A');
    Serial.println("Enviando: A (Izquierda)");
  } 
  else if (valorY > 700) {
    BTSerial.write('D');
    Serial.println("Enviando: D (Derecha)");
  } 
  else if (valorX < 300) {
    BTSerial.write('S');
    Serial.println("Enviando: S (Atrás)");
  } 
  else if (valorX > 700) {
    BTSerial.write('W');
    Serial.println("Enviando: W (Adelante)");
  } else {
    BTSerial.write('Q');
    Serial.println("Enviando: Q (Frenado)");
  }

  delay(100); // Pausa para no saturar el Bluetooth
}
