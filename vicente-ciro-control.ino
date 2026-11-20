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
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toLowerCase();

    if (comando.length() == 0) return;

    if (comando == "menu") {
      Serial.println("\n--- MENU DISPONIBLE ---");
      Serial.println("- papas fritas");
      Serial.println("- milanesa");
      Serial.println("- hamburguesa");
      Serial.println("- licuado");
      Serial.println("-----------------------");
    } else if (comando == "papas fritas" || comando == "papasfritas") {
      Serial.println("Comida recibida: Preparando Papas Fritas...");
      BT.write("Papas");
    } else if (comando == "milanesa") {
      Serial.println("Comida recibida: Marchando una Milanesa...");
      BT.write("Mila");
    } else if (comando == "hamburguesa" || comando == "haburgesa") {
      Serial.println("Comida recibida: Armando la Hamburguesa...");
      BT.write("Hambu");
    } else if (comando == "licuado") {
      Serial.println("Bebida recibida: Licuando frutas...");
      BT.write("Liq");
    } else if (comando == "w" || comando == "W") {
      Serial.println("Avanzando...");
      BT.write("W");
      delay(500);
      BT.write("Q");
    } else if (comando == "a" || comando == "A") {
      Serial.println("Girando ~45° a la izquierda...");
      BT.write("A");
      delay(500);
      BT.write("Q");
    } else if (comando == "d" || comando == "D") {
      Serial.println("Girando ~45° a la derecha...");
      BT.write("D");
      delay(500);
      BT.write("Q");
    }  else {
      Serial.print("Comando desconocido: '");
      Serial.print(comando);
      Serial.println("'. Intente con 'menu'.");
    }
  }
}
