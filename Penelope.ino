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
void loop() 
{
  // put your main code here, to run repeatedly:
  forward();
}
