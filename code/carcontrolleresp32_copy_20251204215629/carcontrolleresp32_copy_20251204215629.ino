
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Controle de direção
#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 15

// Controle de velocidade (ENA/ENB)
#define ENA 25
#define ENB 26

void setup() {
  // Pinos de direção
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Pinos de habilitação (PWM)
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Garantir que os motores estão DESLIGADOS no início
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);  // Começa em LOW
  digitalWrite(ENB, LOW);

  Serial.begin(115200);
  SerialBT.begin("CarroRC");
  Serial.println("Aguardando comando Bluetooth...");
}

void parar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void frente() {
  // Direção
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Velocidade (100% = 255)
  digitalWrite(ENA, HIGH);  // ou analogWrite(ENA, 200) se quiser menos velocidade
  digitalWrite(ENB, HIGH);
}

void re() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    Serial.printf("Recebido: '%c'\n", cmd);

    switch (cmd) {
      case 'F': frente(); break;
      case 'B': re(); break;
      case 'L': esquerda(); break;
      case 'R': direita(); break;
      case 'S': parar(); break;
      default: parar();
    }
  }
}