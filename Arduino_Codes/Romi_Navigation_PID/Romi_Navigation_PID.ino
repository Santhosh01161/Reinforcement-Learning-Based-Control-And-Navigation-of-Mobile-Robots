#include "motor.h"
#include "encoders.h"
#include "timer3.h"
#include "kinematics.h"
#include "pid.h"
#include "defs.h"
#include "utils.h"

float l_power;
float r_power;
vector2f velocity;
vector3f waypoint;

MotorController l_motor(L_PWM_PIN, L_DIR_PIN);
MotorController r_motor(R_PWM_PIN, R_DIR_PIN);
Kinematics      kinematics;
PID             left_pid(1.5, 0.02, 0.1);           // PID for controlling left motor
PID             right_pid(1.5, 0.02, 0.1);          // PID for controlling right motor
PID             heading_pid(0.4, 0, 0.0001);   // PID for controlling heading of romi

//PID-1
//PID             x_pid(0.5, 0, 0.01);              // PID for controlling x coordinate
//PID             y_pid(0.5, 0, 0.01);              // PID for controlling y coordinate

//PID-2
//PID             x_pid(0.6, 0, 0.01);              // PID for controlling x coordinate
//PID             y_pid(0.6, 0, 0.01);              // PID for controlling y coordinate

//PID-3
//PID             x_pid(0.7, 0, 0.01);              // PID for controlling x coordinate
//PID             y_pid(0.7, 0, 0.01);              // PID for controlling y coordinate

//PID-4
PID             x_pid(0.8, 0, 0.01);              // PID for controlling x coordinate
PID             y_pid(0.8, 0, 0.01);              // PID for controlling y coordinate

void setup() {
  Serial.begin(9600);
  // Wait for stable connection, report reset.
  delay(1000);
  //  Serial.println("***RESET***");

  setupEncoder0();
  setupEncoder1();
  setupTimer3();

  waypoint.x = 0.98;
  waypoint.y = -0.17;
  waypoint.theta = 0;

  delay(1000);

  reset_pids();
}

void loop() {
  vector3f pose = kinematics.update_pose(speed_r, speed_l);
  float demand_theta = calculate_theta(pose.x, pose.y, waypoint.x, waypoint.y);

  if (has_reached_waypoint(pose, waypoint) == false){
    float rotate_vel = heading_pid.update(demand_theta, pose.theta, true);
    float forward_vel_x = x_pid.update(waypoint.x, pose.x);
    float forward_vel_y = y_pid.update(waypoint.y, pose.y);
  
    float forward_vel = (float) sqrt(pow(forward_vel_x, 2) + pow(forward_vel_y, 2));
  
    l_power = 255 * left_pid.update(forward_vel - rotate_vel, speed_l); //
    r_power = 255 * right_pid.update(forward_vel + rotate_vel, speed_r); //

  }
  else {
    l_power = 0;
    r_power = 0;
    reset_pids();
  }

  send_motor_cltr();

  delay(10);
}

void send_motor_cltr() {
  l_motor.setPower(l_power);
  r_motor.setPower(r_power);
}

void reset_pids() {
  x_pid.reset();
  y_pid.reset();
  heading_pid.reset();
  right_pid.reset();
  left_pid.reset();
}
