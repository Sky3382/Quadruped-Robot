// body.h
#ifndef BODY_H
#define BODY_H

#include "leg.h"
#include "kinematics.h"

class Body {
public:
  Body();

  void setup();
  void update();
  void moveToPose(float x, float y, float z, float roll, float pitch, float yaw);
  void stand();
  void walkStep(float xSpeed, float ySpeed, float turnRate);

private:
  Leg legs[4];
  Vec3 legOrigins[4];
  Vec3 footTargets[4];
};

#endif
