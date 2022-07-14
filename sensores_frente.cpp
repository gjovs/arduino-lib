#include "sensores_frente.h"
//Pinos do Sensores da Frente
int sensores_frente[3] = { 22 , 24,  23};

void setSensoresFrente() {
  for(int i = 0; i < 3; ++i){
    int index = i;
    pinMode(sensores_frente[index], INPUT);
  }
}

int getSensorFrenteDireita() {
  const int intervalo = 50;
  int estado_anterior = 0;
  
    if (millis() - estado_anterior > intervalo) {
      estado_anterior = millis();
      return digitalRead(sensores_frente[0]);
    }
}

int getSensorFrenteMeio() {
  const int intervalo = 50;
  int estado_anterior = 0;
  
    if (millis() - estado_anterior > intervalo) {
      estado_anterior = millis();
      return digitalRead(sensores_frente[1]);
    }
}

int  getSensorFrenteEsquerda() {
  const int intervalo = 50;
  int estado_anterior = 0;
  
    if (millis() - estado_anterior > intervalo) {
      estado_anterior = millis();
      return digitalRead(sensores_frente[2]);
    }
}
