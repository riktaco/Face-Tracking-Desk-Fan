#include <Servo.h>
Servo myServo;

#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define SERVO 6
 
void setup() {
    //---set pin direction
    pinMode(ENABLE,OUTPUT);
    pinMode(DIRA,OUTPUT);
    pinMode(DIRB,OUTPUT);
    myServo.attach(SERVO);
    Serial.begin(9600);
}

void loop() {
    myServo.write(0);
    //---set motor direction
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
    //---set motor speed
    analogWrite(ENABLE,255);
    delay(1000);
    myServo.write(90);
    //---set motor direction
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,HIGH);
    //---set motor speed
    analogWrite(ENABLE,255);
    delay(1000);
    myServo.write(180);
    //---set motor direction
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,LOW);
    //---set motor speed
    analogWrite(ENABLE,0);
    delay(1000);
}