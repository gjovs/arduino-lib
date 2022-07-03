#include "Robot.h"

void Robot::init(int speed, int curva_degree)
{
	setMotores(speed);
	this->curvaValue = curva_degree;
	setSensoresDeCorDireita();
	setSensoresDeCorEsquerda();

	digitalWrite(this->pinoSensorEsquerda[0], HIGH);
	digitalWrite(this->pinoSensorEsquerda[1], HIGH);

	digitalWrite(this->pinoSensorDireita[0], HIGH);
	digitalWrite(this->pinoSensorDireita[1], HIGH);

}

double Robot::getDistance() {
	return this->ultrassonic.read();
}
1
void Robot::setSensoresDeCorEsquerda()
{
	for (int i = 0; i < 4; i++) {
		pinMode(this->pinoSensorEsquerda[i], OUTPUT);
	}
	pinMode(this->pinoSensorEsquerda[4], INPUT);
}
void Robot::setSensoresDeCorDireita()
{
	for (int i = 0; i < 4; i++) {
		pinMode(this->pinoSensorDireita[i], OUTPUT);
	}
	pinMode(this->pinoSensorDireita[4], INPUT);
}

char Robot::getColorEsquerda()
{
	int* rgb = this->getDataColorEsquerda();
	static char color;
	
	//Black
	if (((rgb[0] >= 250) && (rgb[0] <= 255)) && ((rgb[1] >= 250) && (rgb[1] <= 255)) && ((rgb[2] >= 0) && (rgb[2] <= 50)))
	{
		return color = 'B';
	}
	//White 
	if (((rgb[0] >= 190) && (rgb[0] <= 220)) && ((rgb[1] >= 200) && (rgb[1] <= 230)) && ((rgb[2] >= 250) && (rgb[2] <= 255)))
	{
		return color = 'W';
	}
	//Green
	if (rgb[1] > rgb[0] && rgb[1] > rgb[2]) 
	{
		return color = 'G';
	}
}
char Robot::getColorDireita()
{
	int* rgb = this->getDataColorDireita();
	static char color;

	//Black
	if (((rgb[0] >= 250) && (rgb[0] <= 255)) && ((rgb[1] >= 250) && (rgb[1] <= 255)) && ((rgb[2] >= 0) && (rgb[2] <= 50)))
	{
		return color = 'B';
	}
	//White 
	if (((rgb[0] >= 190) && (rgb[0] <= 220)) && ((rgb[1] >= 200) && (rgb[1] <= 230)) && ((rgb[2] >= 250) && (rgb[2] <= 255)))
	{
		return color = 'W';
	}
	//Green
	if (rgb[1] > rgb[0] && rgb[1] > rgb[2])
	{
		return color = 'G';
	}
}

int* Robot::getDataColorEsquerda() {
	
static int data[3];

digitalWrite(this->pinoSensorEsquerda[2], LOW);
digitalWrite(this->pinoSensorEsquerda[3], LOW);

int redValue = pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);
digitalWrite(this->pinoSensorEsquerda[2], HIGH);
delay(200);

int greenValue = pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);
digitalWrite(this->pinoSensorEsquerda[3], HIGH);
delay(200);

int blueValue = pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);

data[0] = redValue;
data[1] = greenValue;
data[2] = blueValue;

return data;
}
int* Robot::getDataColorDireita() {

	static int data[3];

	digitalWrite(this->pinoSensorDireita[2], LOW);
	digitalWrite(this->pinoSensorDireita[3], LOW);

	int redValue = pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);
	digitalWrite(this->pinoSensorDireita[2], HIGH);
	delay(200);

	int greenValue = pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);
	digitalWrite(this->pinoSensorDireita[3], HIGH);
	delay(200);

	int blueValue = pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);

	data[0] = redValue;
	data[1] = greenValue;
	data[2] = blueValue;

	return data;
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
		this->motor[i].run(FORWARD);
	}
	delay(500);
}
void Robot::curva(int lado)
{
	int delayValue = this->curvaValue * 10;
	//Positivo -> direita
	if (lado < 0)
	{
		getMotor(0).run(FORWARD);
		delay(delayValue);

		getMotor(1).run(BACKWARD);
		delay(delayValue);

		getMotor(2).run(FORWARD);
		delay(delayValue);

		getMotor(3).run(BACKWARD);
		delay(delayValue);
	}
	else
	{
		getMotor(0).run(BACKWARD);
		delay(delayValue);

		getMotor(1).run(FORWARD);
		delay(delayValue);

		getMotor(2).run(BACKWARD);
		delay(delayValue);

		getMotor(3).run(FORWARD);
		delay(delayValue);
	}
}
AF_DCMotor Robot::getMotor(int index)
{
	return this->motor[index];
}

//Follow line method
void Robot::followLine()
{
	//Verde
	if (getColorDireita() == 'G' && getColorEsquerda() == 'G')
	{
		//Giro 180º
	}
	if (getColorDireita() == 'G' && (getColorEsquerda() == 'W' || getColorEsquerda() == 'B'))
	{
		// Virar Direita
	}
	if (getColorEsquerda() == 'G' && (getColorDireita() == 'W' || getColorDireita() == 'B'))
	{
		// Virar Esquerda
	}

	//Andar Frente
	if (getColorDireita() == 'B' && getColorEsquerda() == 'B')
	{
		andarFrente();
	}
	if (getColorDireita() == 'W' && getColorEsquerda() == 'W') {
		andarFrente();
	}

	//Curvas 
	if (getColorDireita() == 'B' && getColorEsquerda() == 'W')
	{
		curva(1);
	}
	if (getColorDireita() == 'W' && getColorEsquerda() == 'B')
	{
		curva(-1);
	}

}