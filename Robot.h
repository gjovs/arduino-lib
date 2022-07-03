#include <Arduino.h>
#include <AFMotor.h>

class Robot
{
private:
	//Variables
	byte pin;
	AF_DCMotor motor[4] = {1,2,3,4};
public:
	//Public
	Robot(byte pin);

	//Init
	void init();
	
	//Sensor Cor Methods
	void setSensoresDeCor();

	//Motor Methods
	void setMotores(int speed);
	void andarFrente();

	//Sensor Ultra Methods

};