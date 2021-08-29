/*
   Defines all the common varibile, constants.
   Author: Vishnu Hariharan Anand and Juvith Ghosh
*/

#ifndef _DEFS_H_
#define _DEFS_H_

#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

#define DIR_FWD LOW
#define DIR_BWD HIGH
#define MAX_PWR 100
#define MAX_SPEED 0.1

#define BUZZER_PIN  6

const float pi = 3.1416;
const float wheel_dia = 0.07; // Diameter of Romi Wheel
const int cnt_per_rev = 1440;
const float d_per_count = (wheel_dia * pi) / (cnt_per_rev);
const float l = 0.145; // Wheel Seperation

float bias = 12;

struct vector3f {
  float x = 0;
  float y = 0;
  float theta = 0;
};

//Network Parameters
const int r1 = 16; //Number of Rows for matrix 1
const int c1 = 8; //Number of Coloumns for matrix 1
const int r2 = 16; //Number of Rows for matrix 2
const int c2 = 16; //Number of Coloumns for matrix 2
const int r3 = 2; //Number of Rows for matrix 3
const int c3 = 16; //Number of Coloumns for matrix 3

struct vector2f {
  float left = 0;
  float right = 0;
};

#endif
