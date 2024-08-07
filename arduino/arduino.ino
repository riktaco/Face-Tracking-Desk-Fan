#include <Servo.h>
Servo myServo;

#define ENABLE 11
#define DIRA 9
#define DIRB 10
#define SERVO 3
#define BUTTON 8

int fanSpeed = 0;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50; // Debounce delay in milliseconds

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
    unsigned long currentMillis = millis();
    
    // Button press handling with debounce
    if (digitalRead(BUTTON) == HIGH) {
        if (currentMillis - lastButtonPress >= debounceDelay) {
            lastButtonPress = currentMillis;
            
            // 3 speeds: 0, 125, 250
            if (fanSpeed == 250) {
                fanSpeed = 0;
            } else {
                fanSpeed += 125;
            }
            
            analogWrite(ENABLE, fanSpeed);
        }
    }

    // Servo control via serial input
    if (Serial.available() > 0) {
        int angle = Serial.parseInt();
        if (angle >= 0 && angle <= 180) {
            myServo.write(angle);
        }
    }
}