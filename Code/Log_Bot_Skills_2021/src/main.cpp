/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Dan                                              */
/*    Created:      Mon Mar 01 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor11              motor         11
// Controller1          controller
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor frontRight = motor(PORT1, ratio18_1, false);
motor frontLeft = motor(PORT11, ratio18_1, false);
motor backRight = motor(PORT10, ratio18_1, true);
motor backLeft = motor(PORT20, ratio18_1, true);
motor lift = motor(PORT15, ratio6_1, false);
motor lift2 = motor(PORT16, ratio6_1, true);
motor turntable = motor(PORT17, ratio18_1, false);

controller vexRT = controller(primary);

bool RemoteControlCodeEnabled = true;
bool sideMotorsNeedStop = true;
bool mainMotorsNeedStop = true;

int deadband;

char pattern[] = {'.'};

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (true) {

    // retrieving joystick values and doing the necessary math for mecanum drive
    
    int frontRightVal = vexRT.Axis1.position() - vexRT.Axis2.position() + vexRT.Axis4.position();
    int frontLeftVal = vexRT.Axis1.position() + vexRT.Axis2.position() + vexRT.Axis4.position();
    int backRightVal = vexRT.Axis1.position() + vexRT.Axis2.position() - vexRT.Axis4.position();
    int backLeftVal = vexRT.Axis1.position() - vexRT.Axis2.position() - vexRT.Axis4.position();

    // applying values to motors if they are greater than deadband, stopping motors if less than deadband

    if(abs(frontRightVal) < deadband){
      frontRight.setVelocity(0, percent);
    } else {
      frontRight.setVelocity(frontRightVal, percent);
    }

    if(abs(frontLeftVal) < deadband){
      frontLeft.setVelocity(0, percent);
    } else {
      frontLeft.setVelocity(frontLeftVal, percent);
    }

    if(abs(backRightVal) < deadband){
      backRight.setVelocity(0, percent);
    } else {
      backRight.setVelocity(backRightVal, percent);
    }

    if(abs(backLeftVal) < deadband){
      backLeft.setVelocity(0, percent);
    } else {
      backLeft.setVelocity(backLeftVal, percent);
    }

    // trigger controls

    if(vexRT.ButtonR1.pressing()){
      lift.setVelocity(100, percent);
      lift2.setVelocity(100, percent);
    } else if(vexRT.ButtonR2.pressing()){
      lift.setVelocity(-100, percent);
      lift2.setVelocity(-100, percent);
    } else{
      lift.setVelocity(0, percent);
      lift2.setVelocity(0, percent);
    }

    // button controls

    if(vexRT.ButtonX.pressing()){
      grip.setVelocity(100, percent);
    } else if (vexRT.ButtonB.pressing()){
      grip.setVelocity(-100, percent);
    } else {
      grip.setVelocity(0, percent);
    }

    if (vexRT.ButtonY.pressing()) {
      turntable.rotateTo(90, degrees, false);
      vexRT.rumble(pattern);
    }
    if (vexRT.ButtonA.pressing()) {
      turntable.rotateTo(0, degrees, false);
      vexRT.rumble(pattern);
    }
    
    lift.spin(forward);
    lift2.spin(forward);
    frontRight.spin(forward);
    frontLeft.spin(forward);
    backRight.spin(forward);
    backLeft.spin(forward);
    grip.spin(forward);
  }
}
