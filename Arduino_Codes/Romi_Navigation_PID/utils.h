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

float calculate_theta(float x1, float y1, float x2, float y2){
  float x = x2 -x1;
  float y = y2 -y1;

  float desired_theta = atan2(y,x);

  return desired_theta;
}

boolean has_reached_waypoint(vector3f pose, vector3f waypoint) {
  float dist = distance(pose.x, pose.y, waypoint.x, waypoint.y);
  if (dist <= 0.1) {
    return true;
  }
  return false;
}

#endif
