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
#define setTime 2000

#define distance 70

double rangeA = 0;
double rangeB = 0;
bool lineMode = false;
unsigned int tempo = 0;

void forward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void back()
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

  rangeA = ((rangeA * 340) / 2) / 10000;
  rangeB = ((rangeB * 340) / 2) / 10000;
  
  if(rangeA < distance || rangeB < distance) {
	forward();
  } else {
	spin_right();
  }
}

void line_detector()
{
	if (analogRead(sensorA) > sensorIntensity){
		spin_right();
		lineMode = true; // Muda para o modo que será realizado pelo carro
		tempo = millis();
		
	} else if (analogRead(sensorB) > sensorIntensity){
		spin_left();
		lineMode = true;
		tempo = millis();
		
	} else if (analogRead(sensorT) > sensorIntensity){
		forward();
	}
	if (lineMode == true) { // Outro modo
		if (millis() - tempo >= setTime && millis() - tempo < setTime + 2000) {
			forward();
		}
		if (millis() - tempo >= setTime + 2000) {
			scan();
			lineMode = false;
		}
	}
}

float ReadUltrasonicA()
{
  digitalWrite(trigA,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA,LOW);
  return ((pulseIn(echoA,HIGH) * 340) / 2) / 10000;
}
float ReadUltrasonicB()
{
  digitalWrite(trigB,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB,LOW);
  return ((pulseIn(echoA,HIGH) * 340) / 2) / 10000;
}

void MotorTest()
{
  forward();
  delay(1000);
  back();
  delay(1000);
  stop();
}
void UltrassonicTest()
{
  float range;
  do
  {
    float range = ReadUltrasonicA();
    Serial.println("UltrassonicTestA: ");
    Serial.println(range);
  }while(rangeA > 20);
  
  do
  {
    float range = ReadUltrasonicB();
    Serial.println("UltrassonicTestB: ");
    Serial.println( range);
  }while( range > 20);
}
void LineSensorTest()
{
  int read;
  do
  {
    read = analogRead(sensorA) > sensorIntensity;
    Serial.println("LineSensorTestA: ");
    Serial.println(read);
  }while(read > sensorIntensity);
  
  do
  {
    int read = analogRead(sensorB) > sensorIntensity;
    Serial.println("LineSensorTestB: ");
    Serial.println(read);
  }while(read > sensorIntensity);

  do
  {
    int read = analogRead(sensorT) > sensorIntensity;
    Serial.println("LineSensorTestA: ");
    Serial.println(read);
  }while(read > sensorIntensity);
  
}

void TestAll()
{
  Serial.println("Iniciando: MotorTest");
  delay(1000);
  MotorTest();
  Serial.println("MotorTest concluido");
  delay(1000);


  Serial.println("Iniciando: UltrassonicTest");
  delay(1000);
  UltrassonicTest();
  Serial.println("UltrassonicTest concluido");
  delay(1000);


  Serial.println("Iniciando: LineSensorTest");
  delay(1000);
  LineSensorTest();
  Serial.println("LineSensorTest concluido");
  delay(1000);
}


void setup() {
  Serial.begin(9600);
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

  TestAll();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //line_detector();
  Serial.print("UltrasonicA: ");
  Serial.print(ReadUltrasonicA());
  Serial.print(" UltrassonicB");
  Serial.print(ReadUltrasonicB());
  Serial.println();
}
// arduino-cli compile --fqbn arduino:avr:uno .     ------------ Compilar
// arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .  ------------ Upload
// arduino-cli monitor -p /dev/ttyACM0 ------- SerialMonitor