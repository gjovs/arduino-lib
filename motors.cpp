#include "motors.h"
// Motor Esquerda Frente
int ENA = 13;
int IN1 = 11;
int IN2 = 10;

// Motor Direita Frente
int ENB = 12;
int IN3 = 9;
int IN4 = 8;

//Motor Esquerda Trás
int ENB_TRAS = 6;
int IN4_TRAS = 5;
int IN3_TRAS = 4;

//Motor Direita Trás 
int ENA_TRAS = 7;
int IN2_TRAS = 3;
int IN1_TRAS = 2;
void setMotores() {
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT); 
  //TRAS
  pinMode(IN1_TRAS, OUTPUT);
  pinMode(IN2_TRAS, OUTPUT);
  pinMode(IN3_TRAS, OUTPUT);
  pinMode(IN4_TRAS, OUTPUT);
  pinMode(ENA_TRAS, OUTPUT);
  pinMode(ENB_TRAS, OUTPUT); 

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  digitalWrite(IN1_TRAS, LOW);
  digitalWrite(IN2_TRAS, LOW);
  digitalWrite(IN3_TRAS, LOW);
  digitalWrite(IN4_TRAS, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  analogWrite(ENA_TRAS, 255);
  analogWrite(ENB_TRAS, 255);
}
void frente() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN3_TRAS, LOW);
  digitalWrite(IN4_TRAS, HIGH);

  digitalWrite(IN1_TRAS, LOW);
  digitalWrite(IN2_TRAS, HIGH);
}
