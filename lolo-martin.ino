void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(A4, INPUT);
  analogRead(A4);
 
}

void loop() {
  if(analogRead(A4) >511){
    digitalWrite(3, HIGH);
    }
    if(analogRead(A4) <511){
    digitalWrite(3, LOW);
    
    }
}   
