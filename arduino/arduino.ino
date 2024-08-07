#include <Servo.h>
Servo myServo;

#define ENABLE 11
#define DIRA 9
#define DIRB 10
#define SERVO 13
#define BUTTON 8

int fanSpeed = 0;

void setup() {
    // Set pins
    pinMode(ENABLE,OUTPUT);
    pinMode(DIRA,OUTPUT);
    pinMode(DIRB,OUTPUT);
    pinMode(BUTTON, INPUT);

    myServo.attach(SERVO);
    Serial.begin(115200);
    while (!Serial) {
    ;  // Wait for serial port to connect.
    }
    Serial.println("Ready to receive data");

    // Set the servo to the middle position
    myServo.write(90);
    // Set motor direction
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
    // Set motor speed
    analogWrite(ENABLE,0);
}

void loop() {
    if(Serial.available() > 0) {
        myServo.write(Serial.parseInt());
    } else if(digitalRead(BUTTON) == HIGH) {
        // 3 speeds: 0, 125, 250
        if(fanSpeed == 250) {
            fanSpeed = 0;
        } else {
            fanSpeed += 125;
        }
        analogWrite(ENABLE, fanSpeed);
        delay(200); // Debounce
    }
}