// body.cpp
#include "body.h"
#include "config.h"
#include "leg.h"

Body::Body() :
  legs {
    Leg(0, {-40, 125, 0}, false),
    Leg(1, { 40, 125, 0}, true),
    Leg(2, {-40, -125, 0}, false),
    Leg(3, { 40, -125, 0}, true)
  },
  footTargets {
    {-80,  125, STD_LEG_HEIGHT},
    { 80,  125, STD_LEG_HEIGHT},
    {-80, -125, STD_LEG_HEIGHT},
    { 80, -125, STD_LEG_HEIGHT}
  } {}

void Body::setup() {
  pwmController.begin();
  pwmController.setPWMFreq(50);
}

void Body::update() {
  for (int i = 0; i < 4; ++i)
    legs[i].gotoPosition(footTargets[i]);
}

void Body::moveToPose(float x, float y, float z, float roll, float pitch, float yaw) {
  Vec3 bodyPos = {x, y, z};

  for (int i = 0; i < 4; ++i) {
    Vec3 legBase = bodyPos + rotateMatrix(legOrigins[i], roll, pitch, yaw);
    FootPosition target = {
      footTargets[i].x - legBase.x,
      footTargets[i].y - legBase.y,
      footTargets[i].z - legBase.z
    };
    legs[i].gotoPosition(target, roll);
  }
}

void Body::stand() {
  for (int i = 0; i < 4; ++i)
    legs[i].gotoPosition(footTargets[i]);
}

void Body::walkStep(float xSpeed, float ySpeed, float turnRate) {
  // (future implementation: gait scheduling)
}
