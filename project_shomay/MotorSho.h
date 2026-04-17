#ifndef MotorSho_h
#define MotorSho_h

#include <Arduino.h>

class MotorSho {
    public:
        void begin(int in1, int in2, int pwm);
        void setSpeed(int speed);
        void stop();

    private:
        int pinIN1;
        int pinIN2;
        int pinPWM;
};

#endif