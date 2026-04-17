#ifndef PIDSho_h
#define PIDSho_h

#include <Arduino.h>

class PIDSho {
    public:
        void setConstants(float kP, float kI, float kD);
        float output(float error);
        void reset();

    private:
        float kP_, kI_, kD_;
        float lastError = 0;
        unsigned long lastUpdate = 0;
        float pOut = 0, iOut = 0, dOut = 0;
};

#endif