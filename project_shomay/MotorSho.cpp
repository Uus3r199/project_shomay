#include "MotorSho.h"

void MotorSho::begin(int in1, int in2, int pwm) {
    pinIN1 = in1;
    pinIN2 = in2;
    pinPWM = pwm;

    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
    pinMode(pinPWM, OUTPUT);
}

void MotorSho::setSpeed(int speed) {
    speed = constrain(speed, -255, 255);

    if(speed >= 0) {
        // Forward
        digitalWrite(pinIN1, HIGH);
        digitalWrite(pinIN2, LOW);
    } else {
        // Reverse
        digitalWrite(pinIN1, LOW);
        digitalWrite(pinIN2, HIGH);
    }

    analogWrite(pinPWM, abs(speed));
}

void MotorSho::stop() {
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, HIGH);
    analogWrite(pinPWM, 0);
}