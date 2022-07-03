#include "Robot.h"

void Robot::init(int speed, int curva_degree, int distanceValue)
{
	setMotores(speed);
	this->curvaValue = curva_degree;
	this->minDistanceValue = distanceValue;
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
		if (validateGreen('L')) {
			return color = 'G';
		};
		return color = 'B';
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
		if (validateGreen('D')) {
			return color = 'G';
		};
		return color = 'B';
	}
}

int* Robot::getDataColorEsquerda() 
{
	
	static int data[3];

	digitalWrite(this->pinoSensorEsquerda[2], LOW);
	digitalWrite(this->pinoSensorEsquerda[3], LOW);

	int redValue = this->getRed('L');
	digitalWrite(this->pinoSensorEsquerda[2], HIGH);
	delay(200);

	int greenValue = this->getGreen('L');
	digitalWrite(this->pinoSensorEsquerda[3], HIGH);
	delay(200);

	int blueValue = getBlue('L');

	data[0] = redValue;
	data[1] = greenValue;
	data[2] = blueValue;

	return data;
}
int* Robot::getDataColorDireita() {

	static int data[3];

	digitalWrite(this->pinoSensorDireita[2], LOW);
	digitalWrite(this->pinoSensorDireita[3], LOW);

	int redValue = this->getRed('D');
	digitalWrite(this->pinoSensorDireita[2], HIGH);
	delay(200);

	int greenValue = getGreen('D');
	digitalWrite(this->pinoSensorDireita[3], HIGH);
	delay(200);

	int blueValue = getBlue('D');

	data[0] = redValue;
	data[1] = greenValue;
	data[2] = blueValue;

	return data;
}
bool Robot::validateGreen(char lado)
{
	stop();
	delay(500);
	if (lado == 'L')
	{
		
		digitalWrite(this->pinoSensorEsquerda[2], LOW);
		digitalWrite(this->pinoSensorEsquerda[3], LOW);

		int redValue = this->getRed('L');
		digitalWrite(this->pinoSensorEsquerda[2], HIGH);
		delay(200);

		int greenValue = this->getGreen('L');
		digitalWrite(this->pinoSensorEsquerda[3], HIGH);
		delay(200);

		int blueValue = getBlue('L');

		if (greenValue > redValue && greenValue > blueValue)
		{
			return true;
		}
		return false;
	} 
	else
	{
		digitalWrite(this->pinoSensorDireita[2], LOW);
		digitalWrite(this->pinoSensorDireita[3], LOW);

		int redValue = this->getRed('D');
		digitalWrite(this->pinoSensorDireita[2], HIGH);
		delay(200);

		int greenValue = getGreen('D');
		digitalWrite(this->pinoSensorDireita[3], HIGH);
		delay(200);

		int blueValue = getBlue('D');

		if (greenValue > redValue && greenValue > blueValue)
		{
			return true;
		}
		return false;
	}

}

//Getter Colors Values
int Robot::getRed(char lado)
{
	if (lado  == 'L')
	{
		return pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);
	}
	else
	{
		return pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);
	}
}
int Robot::getGreen(char lado)
{
	if (lado == 'L')
	{
		return pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);
	}
	else
	{
		return pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);
	}
}
int Robot::getBlue(char lado)
{
	if (lado == 'L')
	{
		return pulseIn(this->pinoSensorEsquerda[4], digitalRead(this->pinoSensorEsquerda[4]) == HIGH ? LOW : HIGH);
	}
	else
	{
		return pulseIn(this->pinoSensorDireita[4], digitalRead(this->pinoSensorDireita[4]) == HIGH ? LOW : HIGH);
	}
}

// Motores
void Robot::setMotores(int speed)
{
	for (int i = 0; i < 4; ++i) {
		this->motor[i].setSpeed(speed);
	}
}
void Robot::runForward(int time = 500)
{
	for (int i = 0; i < 4; ++i) {
		this->motor[i].run(FORWARD);
	}
	delay(time);
}
void Robot::turn(int lado)
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
void Robot::stop()
{
	for (int i = 0; i < 4; ++i) {
		this->motor[i].run(RELEASE);
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
		runForward();
	}
	if (getColorDireita() == 'W' && getColorEsquerda() == 'W') {
		runForward();
	}

	//Curvas 
	if (getColorDireita() == 'B' && getColorEsquerda() == 'W')
	{
		turn(1);
	}
	if (getColorDireita() == 'W' && getColorEsquerda() == 'B')
	{
		turn(-1);
	}

}

//Dodge Obstacule

void Robot::dodgeObstacule()
{
	int counter = 0;
	
	stop();

	while (getDistance() <= this->minDistanceValue)
	{
		turn(1);
		counter++;
	}
	
	runForward(2000);
	
	counter = counter * 2;

	for (int i = counter; i <= 0; --i)
	{
		turn(-1);
	}
	
	runForward(2000);
}