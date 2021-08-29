/*
   Kinematics calculates the pose of the romi using Differential Drive Kinematics (ICC)
   Ref: http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf
   Author: Vishnu Hariharan Anand
*/

#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_

#include "defs.h"
#include "timer3.h"
#include "utils.h"

class Kinematics {
  public:
    vector3f pose;
    vector3f pose_old;

    vector3f update_pose(float speed_r_local, float speed_l_local);
    void print_pose();
  private:
    unsigned long last_millis = 0;
};

vector3f Kinematics::update_pose(float speed_r_local, float speed_l_local) {

  //Calculate how much time (in milliseconds) has
  // bassed since the last update call
  // Note, we do this in type "long", and then
  // typecast the final result to "float".
  long time_now = millis();
  long diff_time = time_now - last_millis;
  last_millis = time_now;

  float dt = (float)diff_time / 1000.0;
  float sum = speed_r_local + speed_l_local;
  float diff = speed_r_local - speed_l_local;

  if (abs(sum) < 0.005) {
    pose.x = pose_old.x;
    pose.y = pose_old.y;
    pose.theta = pose_old.theta + (diff * dt / l);
  }
  else if (abs(diff) < 0.03) {
    float s = sum/2;
    pose.x = pose_old.x + s * cos(pose_old.theta) * dt;
    pose.y = pose_old.y + s * sin(pose_old.theta) * dt;
    pose.theta = pose_old.theta;
  } 

  else {
    pose.x = pose_old.x + (sum * cos(pose_old.theta) * dt) / 2;
    pose.y = pose_old.y + (sum * sin(pose_old.theta) * dt) / 2;
    pose.theta = pose_old.theta + (diff * dt / l);
  }

//  pose.theta = constraint_theta(pose.theta);

  pose_old.x = pose.x;
  pose_old.y = pose.y;
  pose_old.theta = pose.theta;

  print_pose();

  return pose;
}

void Kinematics::print_pose() {
//  Serial.print( "x:  ");
  Serial.print( pose.x );
  Serial.print( ",");
//  Serial.print( "y: " );
  Serial.print( pose.y );
  Serial.print( ",");
//  Serial.print( "theta:  ");
  Serial.println( pose.theta * 180 / pi);
}


#endif
