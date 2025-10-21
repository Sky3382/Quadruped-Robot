#include "leg.h"
#include "config.h"
#include "kinematics.h"

extern Adafruit_PWMServoDriver pwmController;

Leg::Leg(int id, LegOrigin origin, bool isRightSide)
  : legId(id), Origin(origin), IsRightSide(isRightSide) {}

void Leg::gotoPosition(const FootPosition& target, float bodyRoll) {
  FootPos = target;
  Angles = calculateIK(target, bodyRoll);
  setServos();
}

LegAngles Leg::calculateIK(const FootPosition& target, float bodyRoll) {
  float x = target.x;
  float y = target.y;
  float z = target.z;

  if (legId == 1 || legId == 3) x = -x;
  y = -y;

  float A = sqrt(z*z + x*x);
  if (A < ROLL_OFFSET) return {0, 0, 0};

  float zprime = sqrt(A*A - ROLL_OFFSET*ROLL_OFFSET);
  float a1 = atan(x / z);
  float a2 = acos(ROLL_OFFSET / A);
  float r = a1 + a2;

  float B = sqrt(zprime*zprime + y*y);
  float b1 = atan(y / zprime);
  float b2 = acos(B / (2 * L1));
  float p = b1 + b2;

  float k = acos((L2*L2 + L1*L1 - B*B) / (2 * L1 * L2));

  float rollDeg = degrees(r);
  if (legId == 0 || legId == 2)
    rollDeg -= bodyRoll;
  else
    rollDeg += bodyRoll;

  if (legId == 2 || legId == 3)
    rollDeg = -rollDeg + 180;

  return { rollDeg, degrees(p), degrees(k) };
}

void Leg::moveToAngles(float rollDeg, float hipDeg, float kneeDeg) {
  pwmController.setPWM(RollChannel[legId], 0, angleToPulseRoll(rollDeg));
  pwmController.setPWM(PitchChannel[legId], 0, angleToPulsePitch(hipDeg));
  pwmController.setPWM(KneeChannel[legId], 0, angleToPulseKnee(kneeDeg));
}

void Leg::setServos() {
  moveToAngles(Angles.roll, Angles.hip, Angles.knee);
}

int Leg::angleToPulseRoll(float angle) {
  int minP = MinRoll[legId];
  int maxP = MaxRoll[legId];
  return constrain(map((int)angle, 0, 180, minP, maxP),
                   min(minP, maxP), max(minP, maxP));
}

int Leg::angleToPulsePitch(float angle) {
  int minP = MinPitch[legId];
  int maxP = MaxPitch[legId];
  return constrain(map((int)angle, -45, 135, minP, maxP),
                   min(minP, maxP), max(minP, maxP));
}

int Leg::angleToPulseKnee(float angle) {
  int minP = MinKnee[legId];
  int maxP = MaxKnee[legId];
  return constrain(map((int)angle, 45, 135, minP, maxP),
                   min(minP, maxP), max(minP, maxP));
}
