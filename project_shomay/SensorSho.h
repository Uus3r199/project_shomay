#ifndef SensorSho_h
#define SensorSho_h

#include <Arduino.h>

class SensorSho {
    public:
        void begin(const int pins[8], int emitterPin);
        void calibrate(int ledPin);
        int getPos();
        bool isOut();

    private:
        int sensorPins[8];
        int emitterPin;
        int sensorMin[8];
        int sensorMax[8];
        
        bool outside = false;
        int lastPosition = 3500;
};

#endif