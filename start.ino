#include <AFMotor.h>
#include <Ultrasonic.h>
#include <tcs3200.h>
#include "sensores_meio.h"
#include "sensores_frente.h"
#include "motors.h"

bool verde_esquerda, verde_direita;
int data_meio[5];
int data_frente[3];


//PID VALUES
float kp = 25;
float ki = 0;
float kd = 25;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float last_error = 0, last_I = 0;

void setup()
{
  setSensoresMeio();
  setSensoresFrente();
  setMotores();
  Serial.begin(9600);
  stop();
}

void loop()
{    
    printar_dados_dos_sensores(data_meio);
    read_sensors_value();
    calculate_pid();
    controle_motores_linha();
}
void read_sensors_value()
{
    // Condicional Verde
    verde_esquerda = filter_color_green( getColorLeft(), getWhiteLeft() );
    verde_direita = filter_color_green( getColorRight(), getWhiteRight() );
    
    // Dados dos sensores de refletancia do meio e frente
    data_meio[4] = sens_pontaDireita();
    data_meio[3] = sens_direita(); //Cor 
    data_meio[2] = sens_meio();
    data_meio[1] = sens_esquerda(); //Cor 
    data_meio[0] = sens_pontaEsquerda(); 
    
    data_frente[0] = getSensorFrenteDireita();
    data_frente[1] = getSensorFrenteMeio();
    data_frente[2] = getSensorFrenteEsquerda();
    
    // Atribui o valor do erro
    error = getError();
}
float getError() {

  
  if ((data_meio[0] == 1) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0))
    error = 3;
  else if ((data_meio[0] == 1) && (data_meio[1] == 1) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0))
    error = 2;
  else if ((data_meio[0] == 0) && (data_meio[1] == 1) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 0))
    error = 1;
  else if ((data_meio[0] == 0) && (data_meio[1] == 1) && (data_meio[2] == 1) && (data_meio[3] == 0) && (data_meio[4] == 0))
    error = 0;
  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 1) && (data_meio[3] == 0) && (data_meio[4] == 0))
    error = 0;
  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 1) && (data_meio[3] == 1) && (data_meio[4] == 0))
    error = -1;
  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 1) && (data_meio[4] == 0))
    error = -2;
  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 0) && (data_meio[4] == 1))
    error = -3;
//  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 0) && (data_meio[3] == 1) && (data_meio[4] == 1)) // Turn robot left side
//    error = 100;
//  else if ((data_meio[0] == 0) && (data_meio[1] == 0) && (data_meio[2] == 1) && (data_meio[3] == 1)) // Turn robot right side
//    error = 101;
  else if ((data_meio[0] == 1) && (data_meio[1] == 1) && (data_meio[2] == 1) && (data_meio[3] == 1)) // Turn left side or stop
    error = 0;
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
  int velocidade_motor_esquerda = 95 - PID_value;
  int velocidade_motor_direita =  95 + PID_value;
  
  velocidade_motor_esquerda = constrain(velocidade_motor_esquerda, 0, 255);
  velocidade_motor_direita = constrain(velocidade_motor_direita, 0, 255);

  
  setVeloMotoresEsquerda(velocidade_motor_esquerda);
  setVeloMotoresDireita(velocidade_motor_direita - 30);


  Serial.print(velocidade_motor_esquerda);
  Serial.print(velocidade_motor_direita);

  frente();
}

// Printar os Dados
void printar_dados_dos_sensores(int* data)
{
    Serial.print("Sensores -> ");
    //  Printar dados do Sensores
    Serial.print("Ponta da Esquerda: ");
    Serial.print(data[4]);
    Serial.print(" Esquerda: ");
    Serial.print(data[3]);
    Serial.print(" Meio: ");
    Serial.print(data[2]);
    Serial.print(" Direita: ");
    Serial.print(data[1]);
    Serial.print(" Ponta da Direita: ");
    Serial.print(data[0]);
    Serial.println();
} 
void print_dados_frente(int* data) 
{
    Serial.print("Sensores -> ");
    Serial.print("Esquerda: ");
    Serial.print(data[0]);
    Serial.print("Meio: ");
    Serial.print(data[1]);
    Serial.print("Direita: ");
    Serial.print(data[2]);
    Serial.println();
}
