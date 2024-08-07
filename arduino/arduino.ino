#include <Servo.h>
Servo myServo;

#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define SERVO 9
 
void setup() {
    // Set pins
    pinMode(ENABLE,OUTPUT);
    pinMode(DIRA,OUTPUT);
    pinMode(DIRB,OUTPUT);
    myServo.attach(SERVO);
    Serial.begin(115200);
    while (!Serial) {
    ;  // Wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Ready to receive data");

    // Set the servo to the middle position
    myServo.write(90);
    // Set motor direction
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
    // Set motor speed
    analogWrite(ENABLE,200);
}

void loop() {
    if(Serial.available() > 0) {
        myServo.write(Serial.parseInt());
    }
}