// kinematics.cpp
#include "kinematics.h"
#include <math.h>

Vec3 rotateMatrix(const LegOrigin& origin, float degRoll, float degPitch, float degYaw) {
  float roll = radians(degRoll);
  float pitch = radians(degPitch);
  float yaw = radians(degYaw);

  float cy = cos(yaw);
  float sy = sin(yaw);
  float cp = cos(pitch);
  float sp = sin(pitch);
  float cr = cos(roll);
  float sr = sin(roll);

  Vec3 M[3] = {
    {cy*cr - sy*sp*sr, sy*cp, cy*sr + sy*sp*cr},
    {-sy*cr - cy*sp*sr, cy*cp, -sy*sr + cy*sp*cr},
    {-cp*sr, -sp, cp*cr}
  };

  return {
    M[0].x * origin.x + M[0].y * origin.y + M[0].z * origin.z,
    M[1].x * origin.x + M[1].y * origin.y + M[1].z * origin.z,
    M[2].x * origin.x + M[2].y * origin.y + M[2].z * origin.z
  };
}
