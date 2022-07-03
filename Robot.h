#include <Arduino.h>
#include <AFMotor.h>
#include <Ultrasonic.h>

class Robot
{

private:
	//Variables

	//Array with the pins of the colors sensors
	int pinoSensorEsquerda[5] = { 1,2,3,4,5 };
	int pinoSensorDireita[5] = { 6,7,8,9,10 };
	
	//Array with the motors
	AF_DCMotor motor[4] = {1,2,3,4};
	
	//Instance of Ultra

	Ultrasonic ultrassonic = { 12,13 };
	
	//Value of the curve (degree)
	int curvaValue;

	//GET - Data of Sensors
	int* getDataColorEsquerda();
	int* getDataColorDireita();

public:

	//Init
	void init(int speed, int curva_degree);
	
	//Sensor Cor Methods
	void setSensoresDeCorEsquerda();
	void setSensoresDeCorDireita();
	char getColorEsquerda();
	char getColorDireita();
	//Motor Methods
	void setMotores(int speed);
	void andarFrente();
	void curva(int lado);
	AF_DCMotor getMotor(int index);

	//Sensor Ultra Methods
	double getDistance();

	//Follow line

	void followLine();
	
};