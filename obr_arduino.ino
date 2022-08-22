/* Motores */
const int PINO_ENA = 6;
const int PINO_ENB = 5;
const int PINO_IN1 = 4;
const int PINO_IN2 = 3;
const int PINO_IN3 = 8;
const int PINO_IN4 = 7;
/*         SENSORES DE COR     */
// Left tcs3200
#define S0Left 29
#define S1Left 30
#define S2Left 31
#define S3Left 32
#define OUTLeft 33
// Right tcs3200
#define S0Right 34
#define S1Right 35
#define S2Right 36
#define S3Right 37
#define OUTRight 38
/*         FIM DO SENSORES DE COR    */

// definição de pinos para os sensores de seguir linha
const int sensorDireita = 28;
const int sensorMeio = 27;
const int sensorEsquerda = 26;

// variaveis de controle do seguir linha
int error = 0;
// error = 0 | 100 = frente
// error = 1 = esquerda
// error = 2 = direita

int direita = 0;
int meio = 0;
int esquerda = 0;
// Right
int redFrequencyRight = 0;
int greenFrequencyRight = 0;
int blueFrequencyRight = 0;
// Left
int redFrequencyLeft = 0;
int greenFrequencyLeft = 0;
int blueFrequencyLeft = 0;

#define echoPin 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration;
int distanceForward; // CM

const int default_speed = 150;
int speed_motors = 0;

void setup() {
  // velo motores
  analogWrite(PINO_ENA, default_speed);
  analogWrite(PINO_ENB, default_speed);
  // motores
  pinMode(PINO_ENA, OUTPUT);
  pinMode(PINO_ENB, OUTPUT);
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(PINO_IN3, OUTPUT);
  pinMode(PINO_IN4, OUTPUT);
  // ultra
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  // Setting the outputs colors
  pinMode(S0Left, OUTPUT);
  pinMode(S1Left, OUTPUT);
  pinMode(S2Left, OUTPUT);
  pinMode(S3Left, OUTPUT);
  pinMode(OUTLeft, INPUT);
  // 20%
  digitalWrite(S0Left, HIGH);
  digitalWrite(S1Left, LOW);
  //
  pinMode(S0Right, OUTPUT);
  pinMode(S1Right, OUTPUT);
  pinMode(S2Right, OUTPUT);
  pinMode(S3Right, OUTPUT);
  pinMode(OUTRight, INPUT);
  // 20%
  digitalWrite(S0Right, HIGH);
  digitalWrite(S1Right, LOW);

  // sensores refletancia
  pinMode(sensorDireita, INPUT);
  pinMode(sensorMeio, INPUT);
  pinMode(sensorEsquerda, INPUT);
  Serial.begin(9600);
}

void loop() {
  readColors();
  readSensors();
  calculateError();
  Serial.print(error);
  Serial.println();
  printColors();
  if (error == 0 || error == 100) {
    frente();
  } else if (error == 1) {
    // ir para frente por x tempo
    do {
      virarDireita();
      // ler os sensores e calcula o erro
      readSensors();
      calculateError();
    } while (error != 100);
  } else if (error == 2) {
    // ir para frente por x tempo
    do {
      virarEsquerda();
      // ler os sensores e calcula o erro
      readSensors();
      calculateError();
    } while (error != 100);
  }

  delay(100);
}
void readUltrassonicForward() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceForward = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}
void readColors() {
  digitalWrite(S2Left, LOW);
  digitalWrite(S3Left, LOW);
  redFrequencyLeft = pulseIn(OUTLeft, LOW);
  digitalWrite(S2Left, HIGH);
  digitalWrite(S3Left, HIGH);
  greenFrequencyLeft = pulseIn(OUTLeft, LOW);
  digitalWrite(S2Left, LOW);
  digitalWrite(S3Left, HIGH);
  blueFrequencyLeft = pulseIn(OUTLeft, LOW);
  // RIGHT
  digitalWrite(S2Right, LOW);
  digitalWrite(S3Right, LOW);
  redFrequencyRight = pulseIn(OUTRight, LOW);
  digitalWrite(S2Right, HIGH);
  digitalWrite(S3Right, HIGH);
  greenFrequencyRight = pulseIn(OUTRight, LOW);
  digitalWrite(S2Right, LOW);
  digitalWrite(S3Right, HIGH);
  blueFrequencyRight = pulseIn(OUTRight, LOW);
  delay(100);
}
void readSensors() {
  direita = !digitalRead(sensorDireita);
  meio = !digitalRead(sensorMeio);
  esquerda = !digitalRead(sensorEsquerda);
}

bool validateGreenLeft() {
  int counter = 0;
  for (int i = 200; i >= 0; i--) {
    readColors();
    if ((redFrequencyLeft < greenFrequencyLeft) && (blueFrequencyLeft < greenFrequencyLeft)) {
      counter++;
    }
  }
  if (counter >= 100) {
    return true;
  }
  return false;
}

bool validateGreenRight() {
  int counter = 0;
  for (int i = 200; i >= 0; i--) {
    readColors();
    if ((redFrequencyRight < greenFrequencyRight) && (blueFrequencyRight < greenFrequencyRight)) {
      counter++;
    }
  }
  if (counter >= 100) {
    return true;
  }
  return false;
}

void calculateError() {
  // adicionar condicional de verde + validate

  // condições para seguir em frente error = 0;
  if (esquerda == 1 && meio == 1 && direita == 1) {
    error = 0;
  } else if (esquerda == 0 && meio == 0 && direita == 0) {
    error = 0;
  } else if (esquerda == 0 && meio == 1 && direita == 0) {
    error = 100;
  }

  // condições para virar a esquerda
  else if (esquerda == 1 && meio == 1 && direita == 0) {
    error = 1;
  } else if (esquerda == 1 && meio == 0 && direita == 0) {
    error = 1;
  }

  // condições para virar a direita
  else if (esquerda == 0 && meio == 1 && direita == 1) {
    error = 2;
  } else if (esquerda == 0 && meio == 0 && direita == 1) {
    error = 2;
  }
}

void printColors() {
  Serial.print("Cor Esquerda");
  Serial.print("R: ");
  Serial.print(redFrequencyLeft);
  Serial.print("G: ");
  Serial.print(greenFrequencyLeft);
  Serial.print("B: ");
  Serial.print(blueFrequencyLeft);
  Serial.print(" Cor Direita");
  Serial.print("R: ");
  Serial.print(redFrequencyRight);
  Serial.print("G: ");
  Serial.print(greenFrequencyRight);
  Serial.print("B: ");
  Serial.print(blueFrequencyRight);
  Serial.println();
}

void frente() {
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, HIGH);
  //
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarEsquerda() {
  digitalWrite(PINO_IN1, HIGH);
  digitalWrite(PINO_IN2, LOW);
  //
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, HIGH);
}
void virarDireita() {
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, HIGH);
  //
  digitalWrite(PINO_IN3, HIGH);
  digitalWrite(PINO_IN4, LOW);
}
void parar(int timer) {
  digitalWrite(PINO_IN1, LOW);
  digitalWrite(PINO_IN2, LOW);
  //
  digitalWrite(PINO_IN3, LOW);
  digitalWrite(PINO_IN4, LOW);
  delay(timer);
}
