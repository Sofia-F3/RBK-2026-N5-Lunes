
#include <SoftwareSerial.h>

// Bluetooth RX, TX
SoftwareSerial BT(10, 11);

// Motor izquierdo
#define enA 9
#define in1 8
#define in2 7

// Motor derecho
#define enB 3
#define in3 4
#define in4 5

// Velocidad de motores
const int velocidad = 180;

void setup() {

  // Configurar motores
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Iniciar comunicaciones
  Serial.begin(9600);
  BT.begin(9600);

  // Detener motores al iniciar
  parar();

  Serial.println("AUTO LISTO");
  Serial.println("Esperando comandos Bluetooth...");
}

void loop() {

  if (BT.available() > 0) {

    char dato = BT.read();

    // AVANZAR
    if (dato == 'W' || dato == 'w') {

      Serial.println("Avanzando...");
      adelante();

    }

    // GIRAR IZQUIERDA
    else if (dato == 'A' || dato == 'a') {

      Serial.println("Girando izquierda...");
      izquierda();

    }

    // GIRAR DERECHA
    else if (dato == 'D' || dato == 'd') {

      Serial.println("Girando derecha...");
      derecha();

    }

    // DETENER
    else  {

      Serial.println("Deteniendo...");
      parar();

    }

  }

}

// ---------------- MOVIMIENTOS ----------------

void adelante() {

  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void izquierda() {

  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void derecha() {

  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void parar() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, 0);
  analogWrite(enB, 0);

}
