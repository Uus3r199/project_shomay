#include "MotorSho.h"
#include "SensorSho.h"
#include "PIDSho.h"

// ================= HARDWARE PINS =========================
const int SENSOR_PINS[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
const int EMITTER_PIN = 11;

const int AIN1 = 8, AIN2 = 9, PWMA = 5;
const int BIN1 = 4, BIN2 = 7, PWMB = 6;

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 10;
const int LED_PIN = 13;

// ================= OBJECT INSTANTIATION =================
MotorSho motorLeft;
MotorSho motorRight;
SensorSho sensors;
PIDSho pid;

// ================= PID TUNING ===========================
float kP = 0.10;
float kI = 0.00;
float kD = 0.12;
int baseSpeed = 60; // adjust speed here (max speed = 255)
// ========================================================

void setup() {
  Serial.begin(9600);

  // Setup UI
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Initialize Objects
  motorLeft.begin(AIN1, AIN2, PWMA);
  motorRight.begin(BIN1, BIN2, PWMB);
  sensors.begin(SENSOR_PINS, EMITTER_PIN);
  pid.setConstants(kP, kI, kD);

  // Wait for user to press button before calibrating
  waitForButton();
  beep();
  
  // Calibrate - Manually sweep robot over line while LED is on for 5secs
  sensors.calibrate(LED_PIN);
  beep(); delay(100); beep(); // double beep = calibrated

  // Wait for user to place on track and press start
  waitForButton();
  beep();
  delay(1000);
}

void loop() {
  // Get position error
  int error = sensors.getPos();

  // Line Lost Recovery
  if (sensors.isOut()) {
    if (error < 0) { // Lost to the left
      motorLeft.setSpeed(-100);
      motorRight.setSpeed(100);
    } else {         // Lost to the right
      motorLeft.setSpeed(100);
      motorRight.setSpeed(-100);
    }
    return;
  }

  // Get PID Correction
  float correction = pid.output(error);
  motorLeft.setSpeed(baseSpeed + correction);
  motorRight.setSpeed(baseSpeed - correction);
}

// ================= PERIPHERALS ===========================
void waitForButton() {
  while(digitalRead(BUTTON_PIN) == HIGH) delay(10);
  while(digitalRead(BUTTON_PIN) == LOW) delay(10);
}

void beep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
}