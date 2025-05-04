#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

#define ENA 10
#define ENB 11

#define trigA 12
#define echoA 13
#define trigB 8
#define echoB 9

#define sensorA A3
#define sensorB A2
#define sensorT A1
#define sensorIntensity 300
#define setTime 1000

#define distance 70

double rangeA = 0;
double rangeB = 0;
unsigned double tempo = 0;
bool lineMode false;


void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);

  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(sensorT, INPUT);
  

  analogWrite(ENA,200);
  analogWrite(ENB,200);
}
void back()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void forward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void stop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void spin_left()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void spin_right()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void scan()
{
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
  digitalWrite(trigA,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA,LOW);
  rangeA = pulseIn(echoA,HIGH);

  digitalWrite(trigB,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB,LOW);
  rangeB = pulseIn(echoB,HIGH);

  rangeA = ((rangeA * 340) / 2) / 100;
  rangeB = ((rangeB * 340) / 2) / 100;
  
  if(rangeA < distance || rangeB < distance) {
	forward();
  } else {
	spin_right();
  }
}

void line_detector()
{
	if (analogRead(sensorA) < sensorIntensity){
		spin_right();
		lineMode = true; // Muda para o modo que será realizado pelo carro
		if (tempo == 0) //Pega o tempo atual do millis pra começar a contar
			tempo = millis();
		
	} else if (analogRead(sensorB) < sensorIntensity){
		spin_left();
		lineMode = true;
		if (tempo == 0)
			tempo = millis();
		
	} else if (analogRead(sensorT) < sensorIntensity){
		forward();
	}
	if (lineMode == true) { // Outro modo
		if (millis() - tempo >= setTime && millis() - tempo < setTime + 2000) {
			forward();
		}
		if (millis() - tempo >= setTime + 2000) {
			scan();
			lineMode = false;
			tempo = 0;
		}
	}
}
void loop() 
{
  // put your main code here, to run repeatedly:
  forward();
}
