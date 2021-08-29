/*
   Motor Contoller class hepls to send PWM commands to the motors.
   Author: Vishnu Hariharan Anand
*/

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "defs.h"

class MotorController {
  public:
    int dir_pin;
    int pwm_pin;
    MotorController(int pwm_pin, int dir_pin) {
      this->dir_pin = dir_pin;
      this->pwm_pin = pwm_pin;

      // Set our motor driver pins as outputs.
      pinMode( dir_pin, OUTPUT );
      pinMode( pwm_pin, OUTPUT );

      digitalWrite( dir_pin, LOW );
      digitalWrite( pwm_pin, LOW );
    }

    void setPower( float power) {
      if (power < 0) {
        digitalWrite( dir_pin, DIR_BWD );
        power *= -1;
      } else {
        digitalWrite( dir_pin, DIR_FWD );
      }
      if (power > MAX_PWR) {
        power = MAX_PWR;
      }
      if (power < bias) {
        power = 0;
      }

      analogWrite(pwm_pin, power);
    }

};

#endif
