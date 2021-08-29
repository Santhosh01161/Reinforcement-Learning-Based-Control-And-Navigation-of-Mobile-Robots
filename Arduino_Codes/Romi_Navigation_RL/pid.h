/*
   Define the basic pid controller.
   Author: Vishnu Hariharan Anand
   Ref: https://github.com/paulodowd/EMATM0054_20_21/blob/master/Romi_CodeStub/pid.h
*/

#ifndef _PID_H_
#define _PID_H_

#include "utils.h"

class PID {
  public:
    PID(float P, float I, float D);                 // Constructor, not order of P I & D arguments when calling.
    void setGains(float P, float I, float D);       // This function updates the values of the gains
    void reset();                                   // Useful to remove any intergral wind-up
    float update(float demand, float measurement, bool is_heading = false);  // This update takes a demand and measurement.
    void printComponents(); //This function prints the individual components of the control signal and can be used for debugging
    float Kp_output = 0;
    float Ki_output = 0;
    float Kd_output = 0;
  private:
    //Control gains
    float Kp; //Proportional
    float Ki; //Integral
    float Kd; //Derivative

    //Values to store
    float output_signal       = 0;
    float last_error          = 0; //For calculating the derivative term
    float integral_error      = 0; //For storing the integral of the error
    unsigned long last_millis = 0;
};

/*
   Class constructor
   This runs whenever we create an instance of the class
*/
PID::PID(float P, float I, float D)
{
  //Store the gains
  setGains(P, I, D);
  //Set last_millis
  reset();
}

/*
   This function prints the individual contributions to the total contol signal
   You can call this yourself for debugging purposes, or set the debug flag to true to have it called
   whenever the update function is called.
*/
void PID::printComponents() {

  Serial.print(Kp_output);
  Serial.print(", ");
  Serial.print(Kd_output);
  Serial.print(", ");
  Serial.print(Ki_output);
  Serial.print(", ");
  Serial.println(output_signal);

}

void PID::reset() {
  last_error      = 0;
  integral_error  = 0;
  Kp_output       = 0;
  Ki_output       = 0;
  Kd_output       = 0;
  last_millis     = millis();
}

/*
   This function sets the gains of the PID controller
*/
void PID::setGains(float P, float I, float D) {
  Kp = P;
  Kd = D;
  Ki = I;
}

/*
   This is the update function.
   This function should be called repeatedly.
   It takes a measurement of a particular quantity and a desired value for that quantity as input
   It returns an output; this can be sent directly to the motors,
   or perhaps combined with other control outputs
*/
float PID::update(float demand, float measurement, bool is_heading = false) {

  //Calculate how much time (in milliseconds) has
  // bassed since the last update call
  // Note, we do this in type "long", and then
  // typecast the final result to "float".
  long time_now = millis();
  long diff_time = time_now - last_millis;
  last_millis = time_now;

  float dt = (float)diff_time;

  // Calculate error between demand and measurement.
  float error = demand - measurement ;
  if (is_heading){
    error = constraint_theta(error);
  }

  //This represents the error derivative
   float error_delta = (error - last_error)/dt;
   last_error = error;

  // Integral term.
   integral_error += error * dt;

  //Calculate P,I,D Term contributions.
   Kp_output = Kp * error;
   Kd_output = -Kd * error_delta;
   Ki_output = Ki * integral_error;

  //Add the three components to get the total output
  output_signal = Kp_output + Kd_output + Ki_output;


//  if (output_signal > 1){
//    output_signal = 1;
//  }else if (output_signal < -1){
//    output_signal = -1;
//  }

  // Pass the result back.
  return output_signal;
}

#endif
