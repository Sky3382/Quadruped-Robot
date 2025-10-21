#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <MPU6050_light.h>

extern Adafruit_PWMServoDriver pwmController;
extern MPU6050 mpu;

// Servo pulse ranges
const int MinRoll[4]  = {210, 525, 200, 510};
const int MaxRoll[4]  = {525, 210, 520, 190};

const int MinPitch[4] = {200, 515, 195, 525};
const int MaxPitch[4] = {510, 200, 505, 205};

const int MinKnee[4]  = {435, 275, 440, 270};
const int MaxKnee[4]  = {275, 440, 285, 430};

// Servo channels
const int RollChannel[4]  = {0, 3, 6, 9};
const int PitchChannel[4] = {1, 4, 7, 10};
const int KneeChannel[4]  = {2, 5, 8, 11};

// Leg geometry
#define ROLL_OFFSET 40
#define L1 100
#define L2 100
#define STD_LEG_HEIGHT -141

#endif
