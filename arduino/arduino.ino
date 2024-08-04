#include <Servo.h>
Servo myServo;

#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define SERVO 9

String inString = "";  // string to hold input
int angle = 0;
 
void setup() {
    //---set pin direction
    pinMode(ENABLE,OUTPUT);
    pinMode(DIRA,OUTPUT);
    pinMode(DIRB,OUTPUT);
    myServo.attach(SERVO);
    Serial.begin(115200);
    while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Ready to receive data");
    myServo.write(0);
}

void loop() {
    //---set motor direction
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
    //---set motor speed
    analogWrite(ENABLE,200);

    while (Serial.available() > 0) {
        angle = Serial.parseInt();
        myServo.write(angle);
    }
}