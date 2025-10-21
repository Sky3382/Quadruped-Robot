// kinematics.h
#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "leg.h"

struct Vec3 {
  float x, y, z;
};

Vec3 rotateMatrix(const LegOrigin& origin, float roll, float pitch, float yaw);

#endif
