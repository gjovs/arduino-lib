#include "Robot.h"

Robot::Robot(byte pin)
{
	this->pin = pin;
	init();
}
void Robot::init()
{
	pinMode(pin, OUTPUT);
	setMotores(100);
}
void Robot::setSensoresDeCor()
{

}
void Robot::setMotores(int speed)
{
	for (int i = 0; i < 4; ++i) {
		this->motor[i].setSpeed(speed);
	}
}
void Robot::andarFrente()
{
	for (int i = 0; i < 4; ++i) {
		this.motor[i].run(FORWARD);
	}
	delay(500);
}