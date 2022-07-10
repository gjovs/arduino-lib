#include <AFMotor.h>
#include <Ultrasonic.h>
#include <tcs3200.h>
#include "sensores_meio.h"
#include "sensores_frente.h" 
#include "motors.h"
const int init_velocidade = 150;
bool isGreen = false;
bool verde_esquerda;
bool verde_direita;
int data_meio[5];

int* data_frente = 0;


//PID VALUES
float kp = 25;
float ki = 0;
float kd = 15;

float error = 0, P = 0, I =0 , D = 0, PID_value = 0;
float last_error = 0, last_I = 0;



void setup(){
  setSensoresMeio();
  setSensoresFrente();
  setMotores();
  Serial.begin(9600);
  
}

void loop()
{    

  
  frente();
  delay(200);
  read_sensors_value();
  printar_dados_dos_sensores(data_meio);
}

// READ THE ALL THE SENSOR VALUES OF THE ROBOT INSTACE

void read_sensors_value()
{
    // condicional verde    
    verde_esquerda = filter_color_green(getColorLeft(), getWhiteLeft());
    verde_direita = filter_color_green(getColorRight(), getWhiteRight());
    // dados dos sensores de refletancia do meio e frente

    data_meio[0] = sens_pontaEsquerda();
    data_meio[1] = sens_esquerda();
    data_meio[2] = sens_meio();
    data_meio[3] = sens_direita();
    data_meio[4] = sens_pontaDireita(); 
    
    data_frente = getSensoresFrente();
    error = getError();
}
float getError()
{
//  
// data_meio -> array data_meio
// data_frente  -> array data_frente

////  //Todos Branco Meio  
if ( (data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0) )
{
  return 0; //TURN U  
}

//Todos Preto Meio
else if ( (data_meio[0] == 1) && (data_meio[1] == 1) && (data_meio[2] == 1) && (data_meio[3] == 1) && (data_meio[4] == 1) )
{
 return 0; 
}

//////  // Curva 90 Esquerda
else if ( (data_meio[0] == 1) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0) ){
 
  return 3; 
}

//////  // Curva 90 Esquerda
else if ( (data_meio[0] == 1) && (data_meio[1] == 1) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0) )
{

return 2;
}

////  // Curva Suave Esquerda
else if ( (data_meio[0] == 0) && (data_meio[1] == 1) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0) )
{
 
return 1; 
}
////  // Curva Suave Esquerda
else if ( (data_meio[0] == 0) && (data_meio[1] == 1) && (data_meio[2] == 1) && (data_meio[3] == 0) && (data_meio[4] == 0) )
{

return 0.85; 
}
////  // Frente
else if ( (data_meio[0] == 0) && (data_meio[1] == 1) && (data_meio[2] == 1) && (data_meio[3] == 1) && (data_meio[4] == 0) )
{

return 0; 
}
else if ( (data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 1) && (data_meio[3] == 0) && (data_meio[4] == 0) )
{
  frente();
return 0; 
}
////  //Curva 90 Direita
else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 1))
{

return -3;
}
////
////  //Curva 90 Direita
else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 1) && (data_meio[4] == 1))
{

    return -2;
}
////  //Curva Suave Direita
else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 1) && (data_meio[4] == 0))
{
return -1;
}
////  //Curva Suave Direita
else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 1) && (data_meio[3] == 1) && (data_meio[4] == 0))
{
return -0.85;
}
}
void printar_dados_dos_sensores(int* data)
{

    Serial.print("DATA -> ");

    //  Printar dados do Sensores
    Serial.print("Ponta da Direita: ");
    Serial.print(data[4]);
    Serial.print("Direita: ");
    Serial.print(data[3]);
    Serial.print("Meio: ");
    Serial.print(data[2]);
    Serial.print("Esquerda: ");
    Serial.print(data[1]);
    Serial.print("Ponta da Esquerda: ");
    Serial.print(data[0]);
    Serial.println();
} 

void calculate_pid()
{
  
  P = error;
  I = I + last_I;
  D = error - last_error;

  PID_value = (kp * P) + (ki * I) + (kd * D);

  last_I = I;
  last_error = error;

}

void controle_motores_linha()
{
  int left_motor_speed = init_velocidade - PID_value;
  int right_motor_speed =  init_velocidade + PID_value;

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

}
