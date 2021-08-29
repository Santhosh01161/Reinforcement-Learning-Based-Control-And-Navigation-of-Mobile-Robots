/*
   Defines all the helping functions which are commonly used by other classes.
   Author: Vishnu Hariharan Anand
*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include "defs.h"

float constraint_theta(float theta) {
  if (theta > pi) {
    theta -= 2 * pi;
  } else if (theta < -pi) {
    theta += 2 * pi;
  }
  return theta;
}

float distance(float x1, float y1, float x2, float y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

boolean has_reached_home(vector3f pose) {
  if ((abs(pose.x) <= 0.05) ) {
    return true;
  }
  return false;
}

#endif
