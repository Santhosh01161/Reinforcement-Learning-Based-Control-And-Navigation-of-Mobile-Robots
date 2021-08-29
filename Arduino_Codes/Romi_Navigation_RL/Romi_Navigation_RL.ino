#include "motor.h"
#include "encoders.h"
#include "timer3.h"
#include "kinematics.h"
#include "rl_agent.h"
#include "pid.h"
#include "defs.h"

float l_power;
float r_power;
vector2f velocity;
vector3f waypoint;

MotorController l_motor(L_PWM_PIN, L_DIR_PIN);
MotorController r_motor(R_PWM_PIN, R_DIR_PIN);
Kinematics      kinematics;
RLController    rl_controller;
PID             left_pid(1.5, 0.02, 0.1);           // PID for controlling left motor
PID             right_pid(1.5, 0.02, 0.1);          // PID for controlling right motor

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
}

void loop() {
  vector3f pose = kinematics.update_pose(speed_r, speed_l);
  velocity = rl_controller.estimate_velocity(pose, waypoint);

  l_power = 255 * left_pid.update(velocity.left  * wheel_dia / 2, speed_l); // Velocity conversion from rad/sec to m/s
  r_power = 255 * right_pid.update(velocity.right * wheel_dia / 2, speed_r); // Velocity conversion from rad/sec to m/s

  send_motor_cltr();
  
  delay(40);
}

void send_motor_cltr() {
  l_motor.setPower(l_power);
  r_motor.setPower(r_power);
}
