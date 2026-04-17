#include "PIDSho.h"

void PIDSho::setConstants(float p, float i, float d) {
    kP_ = p;
    kI_ = i;
    kD_ = d;
}

float PIDSho::output(float error) {
    unsigned long now = millis();
    unsigned long deltaTime = now - lastUpdate;

    if (deltaTime >= 20) {
        pOut = error * kP_;
        iOut += kI_ * error; // Compute integral
        dOut = (error - lastError) * kD_; // Compute derivative
        
        lastError = error; // Store current error
        lastUpdate = now;
    }

    // Summation of Proportional, Integral, and Derivative outputs
    return pOut + iOut + dOut; 
}

void PIDSho::reset() {
    lastError = 0;
    pOut = 0;
    iOut = 0;
    dOut = 0;
}