#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);

// Pines de control del Motor Izquierdo
#define enA = 9;   
#define in1 = 8;   
#define in2 = 7;
// Pines de control del Motor Derecho
#define enB = 3;   
#define in3 = 5;   
#define in4 = 4;   
// Configura la velocidad de los motores (0 a 255)
const int velocidad = 180; 

#define tiempoGiro45 = 150; 
void setup() {
  // Configurar pines como salidas
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Inicializar comunicación serial
  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("Robot listo. Envía W, A o D para moverlo.");
}

void loop() {
  if (BT.available() > 0) {
    char dato =  BT.read(); // Leer la tecla presionada

    if (dato == 'w' || dato == 'W') {
      Serial.println("Avanzando...");
      adelante();
    } 
    else if (dato == 'S' || dato == 's') {
      Serial.println("Retrocediendo...");
      atras();
    } 
    else if (dato == 'a' || dato == 'A') {
      Serial.println("Girando ~45° a la izquierda...");
      izquierda();
    } 
    else if (dato == 'd' || dato == 'D') {
      Serial.println("Girando ~45° a la derecha...");
      derecha();
    }
  }
}

// Funciones de movimiento
void adelante() {
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  
  // Ambos motores hacia adelante (depende de cómo los cables estén conectados)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void atras() {
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  
  // Ambos motores hacia adelante (depende de cómo los cables estén conectados)
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void izquierda() {
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  
  // Motor izquierdo atrás, Motor derecho adelante
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void derecha() {
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  
  // Motor izquierdo adelante, Motor derecho atrás
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
}
