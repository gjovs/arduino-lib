#include "motors.h"

//MOTOR1
const int ENA = 8; //PWM
const int IN1 = 7;
const int IN2 = 6;
//MOTOR2
const int ENB = 3; //PWM
const int IN3 = 5;
const int IN4 = 4;

// Setters
void setMotores() {
  // Esquerda 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Direita
  pinMode(ENB, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Iniciar Parado
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  //Velocidade Inicial
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}
void setVeloMotoresEsquerda(int velocidade) {
  analogWrite(ENA, velocidade);
}
void setVeloMotoresDireita(int velocidade) {
  analogWrite(ENB, velocidade);
}

// Movimento 
// Default values:
// LOW + HIGH => FRENTE 
// HIGH + LOW => TRÁS
// LOW + LOW => PARADO

void frente() {
  //MOTOR1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  //MOTOR2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void virarDireita() {
  //MOTOR1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  //MOTOR2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void virarEsquerda() {
  //MOTOR1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //MOTOR2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
