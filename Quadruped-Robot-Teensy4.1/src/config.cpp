#ifndef LEG_H
#define LEG_H

#include "config.h"

struct FootPosition {
  float x, y, z;
};

struct LegAngles {
  float roll, hip, knee;
};

struct LegOrigin {
  float x, y, z;
};

class Leg {
public:
  Leg(int id, LegOrigin origin, bool isRightSide);

  void gotoPosition(const FootPosition& target, float bodyRoll = 0);
  LegAngles calculateIK(const FootPosition& target, float bodyRoll = 0);
  void moveToAngles(float rollDeg, float hipDeg, float kneeDeg);
  void setServos();
  LegOrigin getOrigin() const { return Origin; }

  FootPosition FootPos;
  LegAngles Angles;
  LegOrigin Origin;

private:
  int legId;
  bool IsRightSide;

  int angleToPulseRoll(float angle);
  int angleToPulsePitch(float angle);
  int angleToPulseKnee(float angle);
};

#endif
