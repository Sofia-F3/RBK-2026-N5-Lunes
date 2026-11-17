#include <SoftwareSerial.h>

// Pines del Bluetooth en el control (RX, TX)
SoftwareSerial BTSerial(10, 11);

// Pines del Joystick
const int pinX = A0;
const int pinY = A1;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  int valorX = analogRead(pinX); // Izquierda (~0) a Derecha (~1023)
  int valorY = analogRead(pinY); // Arriba (~0) a Abajo (~1023)

  // Mover hacia adelante (Palanca hacia arriba)
  // Nota: Si al empujar hacia adelante no avanza, cambia (< 300) por (> 700)
  if (valorY < 300) {
    BTSerial.write('W');
    Serial.println("Enviando: W (Adelante)");
  } 
  // Girar a la izquierda (Palanca a la izquierda)
  else if (valorX < 300) {
    BTSerial.write('A');
    Serial.println("Enviando: A (Izquierda)");
  } 
  // Girar a la derecha (Palanca a la derecha)
  else if (valorX > 700) {
    BTSerial.write('D');
    Serial.println("Enviando: D (Derecha)");
  }

  delay(100); // Pausa para no saturar el Bluetooth
}
