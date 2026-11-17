#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO_PANTALLA 128 // Ancho de la pantalla OLED
#define ALTO_PANTALLA 64   // Alto de la pantalla OLED

// Declaración del objeto display para conexión I2C (Pin Reset en -1 si no se usa)
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
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

  // Inicializar pantalla en la dirección I2C común (0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Error: No se encuentra la pantalla OLED SSD1306"));
    for(;;); // Bucle infinito si falla
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Mensaje de espera inicial en la OLED
  display.setCursor(10, 25);
  display.print("Esperando pedido...");
  display.display();
  
  Serial.println("Robot listo. Envía W, A o D para moverlo.");
}

void loop() {
  if (BT.available() > 0) {
    char dato =  BT.read(); // Leer la tecla presionada

    if (dato == 'w' || dato == 'W') {
      Serial.println("Avanzando...");
      adelante();
    } 
    else if (dato == 'a' || dato == 'A') {
      Serial.println("Girando ~45° a la izquierda...");
      izquierda();
    } 
    else if (dato == 'd' || dato == 'D') {
      Serial.println("Girando ~45° a la derecha...");
      derecha();
    } else if (dato == 'q' || dato == 'Q') {
      Serial.println("Frenando");
      parar();
    }
  }

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
    } 
    else if (comando == "papas fritas" || comando == "papasfritas") {
      Serial.println("Comida recibida: Preparando Papas Fritas...");
      dibujarPapasFritas();
    } 
    else if (comando == "milanesa") {
      Serial.println("Comida recibida: Marchando una Milanesa...");
      dibujarMilanesa();
    } 
    else if (comando == "hamburguesa" || comando == "haburgesa") {
      Serial.println("Comida recibida: Armando la Hamburguesa...");
      dibujarHamburguesa();
    } 
    else if (comando == "licuado") {
      Serial.println("Bebida recibida: Licuando frutas...");
      dibujarLicuado();
    } 
    else {
      Serial.print("Comando desconocido: '");
      Serial.print(comando);
      Serial.println("'. Intente con 'menu'.");
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


// --- DIBUJOS ADAPTADOS A 128X64 (BLANCO Y NEGRO) ---
void dibujarPapasFritas() {
  display.clearDisplay();
  
  // Dibujamos el texto en pantalla de confirmación
  display.setCursor(0, 0);
  display.print("PAPAS FRITAS RECIBIDAS");

  // Bastones de papas individuales (Líneas / Rectángulos rellenos)
  for (int x = 54; x <= 74; x += 5) {
    display.fillRect(x, 20, 3, 20, SSD1306_WHITE);
  }
  // Papas cruzadas o desalineadas para darle onda
  display.fillRect(52, 23, 3, 17, SSD1306_WHITE);
  display.fillRect(77, 21, 3, 19, SSD1306_WHITE);

  // Paquete contenedor de papas (Trapecio / Rectángulo cortado)
  display.fillRect(48, 35, 34, 28, SSD1306_WHITE);
  
  // Detalle: "M" calada en negro en el centro del paquete
  display.setCursor(62, 45);
  display.setTextColor(SSD1306_BLACK); // Escribe en negro sobre el fondo blanco
  display.print("M");
  
  display.setTextColor(SSD1306_WHITE); // Restauramos color de texto
  display.display();
}

void dibujarMilanesa() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("MILANESA RECIBIDA");

  // El plato (Una elipse o línea horizontal curva inferior)
  display.drawOval(64, 48, 45, 12, SSD1306_WHITE);

  // La milanesa (Un óvalo relleno arriba del plato)
  display.fillOval(64, 43, 35, 15, SSD1306_WHITE);

  // Rodajita de limón arriba (Círculo negro con centro y bordes blancos)
  display.fillCircle(64, 38, 5, SSD1306_BLACK);
  display.drawCircle(64, 38, 5, SSD1306_WHITE);
  display.drawPixel(64, 38, SSD1306_WHITE); // Centro del limón

  display.display();
}

void dibujarHamburguesa() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("HAMBURGUESA RECIBIDA");

  // Pan Superior (Un semicírculo relleno)
  display.fillRoundRect(49, 20, 32, 12, 6, SSD1306_WHITE);

  // Queso derritiéndose (Línea blanca continua que sobresale)
  display.fillRect(45, 33, 40, 2, SSD1306_WHITE);
  display.drawPixel(48, 35, SSD1306_WHITE); // Gota de queso
  display.drawPixel(78, 35, SSD1306_WHITE); // Gota de queso

  // Carne (Un rectángulo negro con bordes blancos para contrastar)
  display.fillRect(47, 36, 36, 8, SSD1306_WHITE);
  display.fillRect(49, 38, 32, 4, SSD1306_BLACK); // Centro vacío para que se note la capa

  // Pan Inferior
  display.fillRoundRect(49, 45, 32, 8, 2, SSD1306_WHITE);

  display.display();
}

void dibujarLicuado() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LICUADO RECIBIDO");

  // Sorbete / Bombilla (Línea diagonal inclinada que va al fondo)
  display.drawLine(74, 15, 60, 50, SSD1306_WHITE);

  // Vaso relleno (Líquido del licuado)
  display.fillRect(52, 28, 24, 30, SSD1306_WHITE);

  // Parte vacía del vaso arriba (Borde)
  display.drawRect(50, 24, 28, 36, SSD1306_WHITE);

  // Burbujitas o espuma arriba (Puntos negros dentro del bloque blanco)
  display.drawPixel(56, 31, SSD1306_BLACK);
  display.drawPixel(62, 33, SSD1306_BLACK);
  display.drawPixel(68, 30, SSD1306_BLACK);
  display.drawPixel(71, 34, SSD1306_BLACK);

  display.display();
}
