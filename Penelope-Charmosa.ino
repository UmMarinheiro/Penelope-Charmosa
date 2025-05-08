#define IN1 6
#define IN2 7
#define IN3 4
#define IN4 5

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
  backA();
  forwardB();
}
void spin_B()
{
  forwardA();
  backB();
}

void line_detector()
{
	if (analogRead(sensorA) > sensorIntensity){
		spin_A();
		lineMode = true; // Muda para o modo que será realizado pelo carro
		tempo = millis();
		
	} else if (analogRead(sensorB) > sensorIntensity){
		spin_B();
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
    read = analogRead(sensorA);
    Serial.println("LineSensorTestA: ");
    Serial.println(read);
  }while(read > sensorIntensity);
  
  do
  {
    int read = analogRead(sensorB);
    Serial.println("LineSensorTestB: ");
    Serial.println(read);
  }while(read > sensorIntensity);

  do
  {
    int read = analogRead(sensorT);
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

  TestAll();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //line_detector();
  scan();
  Serial.print("UltrasonicA: ");
  Serial.print(ReadUltrasonicA());
  Serial.print(" UltrassonicB: ");
  Serial.print(ReadUltrasonicB());
  Serial.println();
}
// arduino-cli compile --fqbn arduino:avr:uno .     ------------ Compilar
// arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .  ------------ Upload
// arduino-cli monitor -p /dev/ttyACM0 ------- SerialMonitor