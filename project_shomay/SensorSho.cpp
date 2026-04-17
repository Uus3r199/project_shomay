#include "SensorSho.h"

void SensorSho::begin(const int pins[8], int emitter) {
    emitterPin = emitter;
    pinMode(emitterPin, OUTPUT);
    digitalWrite(emitterPin, HIGH);

    for(int i = 0; i < 8; i++) {
        sensorPins[i] = pins[i];
        sensorMin[i] = 1023;
        sensorMax[i] = 0;
    }
}

void SensorSho::calibrate(int ledPin) {
    digitalWrite(ledPin, HIGH);
    unsigned long startTime = millis();
    
    // Calibrate for 5 seconds
    while(millis() - startTime < 5000) {
        for(int i = 0; i < 8; i++) {
            int val = analogRead(sensorPins[i]);
            if(val < sensorMin[i]) sensorMin[i] = val;
            if(val > sensorMax[i]) sensorMax[i] = val;
        }
    }
    digitalWrite(ledPin, LOW);
}

int SensorSho::getPos() {
    long numerator = 0;
    long denominator = 0;
    bool onLine = false;

    for (int i = 0; i < 8; i++) {
        int raw = analogRead(sensorPins[i]);
        int mappedValue = map(raw, sensorMin[i], sensorMax[i], 0, 1000);
        mappedValue = constrain(mappedValue, 0, 1000);

        if (mappedValue > 200) {
            onLine = true;
        }

        if (mappedValue > 50) { 
            numerator += (long)mappedValue * (i * 1000);
            denominator += mappedValue;
        }
    }

    outside = !onLine;

    if (denominator == 0) {
        // If lost, return the last known position
        return lastPosition - 3500;
    }

    lastPosition = numerator / denominator;
    
    return lastPosition - 3500; 
}

bool SensorSho::isOut() {
    return outside;
}