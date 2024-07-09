#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor1(1); // Front left tire
AF_DCMotor motor2(2); // Back left tire
AF_DCMotor motor3(3); // Front right tire
AF_DCMotor motor4(4); // Back right tire

const int fireSensorLeft = A0;    // Left fire sensor pin
const int fireSensorRight = A1;   // Right fire sensor pin
const int ledPin = A2;            // LED pin (analog pin)
Servo servoMotor;                 // Servo motor object
int servoPin = 10;                // Servo motor pin

void setup() {
    // Set initial speed of the motors & stop
    motor1.setSpeed(200);
    motor1.run(RELEASE);
    motor2.setSpeed(200);
    motor2.run(RELEASE);
    motor3.setSpeed(200);
    motor3.run(RELEASE);
    motor4.setSpeed(200);
    motor4.run(RELEASE);

    // Initialize fire sensor and LED pin
    pinMode(fireSensorLeft, INPUT);
    pinMode(fireSensorRight, INPUT);
    pinMode(ledPin, OUTPUT);

    // Attach servo to pin
    servoMotor.attach(servoPin);
}

void loop() {
    int fireLeft = digitalRead(fireSensorLeft);
    int fireRight = digitalRead(fireSensorRight);

    if (fireLeft == HIGH) {
        // Fire detected on the left side, turn left
        motor1.run(BACKWARD); // Turn left
        motor2.run(FORWARD);
        motor3.run(FORWARD); // Turn left
        motor4.run(BACKWARD);
        servoMotor.write(0); // Move servo to the left
        analogWrite(ledPin, 255); // Turn on LED
    } else if (fireRight == HIGH) {
        // Fire detected on the right side, turn right
        motor1.run(FORWARD); // Turn right
        motor2.run(BACKWARD);
        motor3.run(BACKWARD); // Turn right
        motor4.run(FORWARD);
        servoMotor.write(180); // Move servo to the right
        analogWrite(ledPin, HIGH); // Turn on LED
    } else {
        // No fire detected, stop
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        servoMotor.write(90); // Center servo
        analogWrite(ledPin, LOW); // Turn off LED
    }
}