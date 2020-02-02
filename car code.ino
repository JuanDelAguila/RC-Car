
#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ET;
Servo myServo;
Servo myServo2;

int DirR;
int AccR;
int MapaR;
int GearR;
int DirRmin;
int AccRmin;
int DirRmax;
int AccRmax;
int distance;
int duration;

#define echoPin 13
#define trigPin 12

struct RECEIVE_DATA_STRUCTURE{ 
  float Dir;
  float Acc;
  float GearS;
};
RECEIVE_DATA_STRUCTURE mydata;
void setup() {
  // put your setup code here, to run once:
  ET.begin(details(mydata), &Serial);
  myServo.attach (10);
  myServo2.attach (11);
  Serial.begin (9600);
  pinMode (7, OUTPUT);
  digitalWrite (7, HIGH);
  pinMode (echoPin, INPUT);
  pinMode (trigPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if (ET.receiveData()){
    GearR = mydata.GearS;
    AccRmin = -13.3333 * (GearR) + 90;
    AccRmax = 13.3333 * (GearR) + 90;
    DirRmin = 7.5 * (GearR) + 35;
    DirRmax = -7.5 * (GearR) + 165; 
    digitalWrite (7, HIGH);
    DirR = map(mydata.Dir, 0, 1023, DirRmax, DirRmin);
    AccR = map(mydata.Acc, 0, 1023, AccRmax, AccRmin);
    myServo.write(DirR);
    myServo2.write(AccR);

    
    digitalWrite(trigPin, LOW);
    delayMicroseconds (2);
    digitalWrite (trigPin, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigPin, LOW);
    duration = pulseIn (echoPin, HIGH);
    Serial.println (distance);
    distance = duration/58.2;
    
    if (distance <= 200){
      if (distance > 0) {
        myServo2.write(50);
        delay (57);
      }
      }
    delay (57);
  //}
//  else{
//    digitalWrite (7, LOW);
//    myServo2.write(90);
//  }
}
