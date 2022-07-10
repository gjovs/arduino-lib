#include "sensores_frente.h"
//Pinos do Sensores da Frente
int sensores_frente[3] = { 1 , 2,  3 };

void setSensoresFrente() {
  for(int i = 0; i < 3; ++i){
    int index = i;
    pinMode(sensores_frente[index], INPUT);
  }
}

int* getSensoresFrente() {
    
  int* data;
  const int intervalo = 50;
  int estado_anterior = 0;
  
  for(int i = 0; i < sizeof(sensores_frente); ++i) {
    if (millis() - estado_anterior > intervalo) {
      estado_anterior = millis();
      data[i] = !digitalRead(sensores_frente[i]);
   }
  }
  return data;
}
