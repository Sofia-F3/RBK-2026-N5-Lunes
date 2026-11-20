#include <SoftwareSerial.h>

// Pines del Bluetooth en el control (RX, TX)
SoftwareSerial BT(10, 11);

void setup() {
  // Inicializar comunicación se
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("Robot listo. Envía W, A o D para moverlo.");
}

void loop() {
  if (Serial.available()) {
    char comando = Serial.read();  // Leer la tecla presionada
    Serial.println(comando);
    if (comando == 'w' || comando == 'W') {
      Serial.println("Moviendo para adelante");
      BT.write("W");
    } else if (comando == 'a' || comando == 'A') {
      Serial.println("Moviendo para atrás");
      BT.write("A");
    } else if (comando == 'd' || comando == 'D') {
      Serial.println("Moviendo para la derecha");
      BT.write("D");
    }
  } 
}
