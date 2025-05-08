#define IN1 7
#define IN2 6
#define IN3 4
#define IN4 5

#define ENA 10
#define ENB 11

#define trigA 12
#define echoA 13
#define trigB 8
#define echoB 9

#define sensorA A2
#define sensorB A3
#define sensorT A1
#define setTime 2000

#define distance 20

double rangeA = 0;
double rangeB = 0;
bool lineMode = false;
unsigned int tempo = 0;

void forwardA()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}
void forwardB()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void backA()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}
void backB()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void stopA()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}
void stopB()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void forward()
{
  forwardA();
  forwardB();
}
void back()
{
  backA();
  backB();
}
void stop()
{
  stopA();
  stopB();
}
void spin_A()
{
  //stopA();
  backA();
  forwardB();
}
void spin_B()
{
  forwardA();
  backB();
  //stopB();
}

void line_detector()
{
	if (analogRead(sensorA)){
		spin_A();
		lineMode = true; // Muda para o modo que será realizado pelo carro
		tempo = millis();
		
	} else if (analogRead(sensorB)){
		spin_B();
		lineMode = true;
		tempo = millis();
		
	} else if (analogRead(sensorT)){
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
  return ((pulseIn(echoB,HIGH) * 340) / 2) / 10000;
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
    Serial.print("UltrassonicTestA: ");
    Serial.println(range);
  }while(rangeA > 20);
  
  do
  {
    float range = ReadUltrasonicB();
    Serial.print("UltrassonicTestB: ");
    Serial.println( range);
  }while( range > 20);
}
void LineSensorTest()
{
  int read;
  do
  {
    read = digitalRead(sensorA);
    Serial.print("LineSensorTestA: ");
    Serial.println(read);
  }while(!read);
  
  do
  {
    read = digitalRead(sensorB);
    Serial.print("LineSensorTestB: ");
    Serial.println(read);
  }while(!read);

  do
  {
    read = digitalRead(sensorT);
    Serial.print("LineSensorTestT: ");
    Serial.println(read);
  }while(!read);
  
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


void scan()
{ 
  rangeA = ReadUltrasonicA();
  rangeB = ReadUltrasonicB();

  switch((rangeA < distance)*2 + (rangeB < distance))
  {
    case 3:
      forward(); // 
      break;
    case 0:
      spin_A(); // Procurar
      break;
    case 2:
      spin_A(); // A detectou girar naquela direcao
      break;
    case 1:
      spin_B(); // B detectou girar naquela direcao
      break;
  }
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

  //TestAll();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //line_detector();
  scan();
}
// arduino-cli compile --fqbn arduino:avr:uno .     ------------ Compilar
// arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .  ------------ Upload
// arduino-cli monitor -p /dev/ttyACM0 ------- SerialMonitor