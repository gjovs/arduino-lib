#ifndef SENSORES_MEIO_H
#define SENSORES_MEIO_H

#include <Arduino.h>

  void setSensoresMeio();
  int sens_meio();
  int sens_direita();
  int sens_esquerda();
  int sens_pontaEsquerda();
  int sens_pontaDireita();
  
  int getColorLeft();
  int getWhiteLeft();
  //
  int getColorRight();
  int getWhiteRight();
  //
  bool filter_color_green(int green, int white);
  int filter_color_line(int white);
  int filter_color_line_right(int white);
  
  bool verificar_verde(char lado);
  void printSensoresMeio(int* data);


#endif
