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

motor leftDrive = motor(PORT11, ratio18_1, false);
motor frontDrive = motor(PORT12, ratio18_1, false);
motor rightDrive = motor(PORT13, ratio18_1, true);
motor rearDrive = motor(PORT14, ratio18_1, true);
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

    // retrieving joystick values and doing the necessary math for square omni drive

    int leftDriveVal = vexRT.Axis3.position();
    int rightDriveVal = vexRT.Axis2.position();
    int frontDriveVal = ((vexRT.Axis3.position()-vexRT.Axis2.position())/2) + vexRT.Axis4.position();
    int rearDriveVal = ((vexRT.Axis2.position()-vexRT.Axis3.position())/2) + vexRT.Axis1.position();
    
    // applying values to motors if they are greater than deadband, stopping motors if less than deadband

    if(abs(leftDriveVal) < deadband){
      leftDrive.setVelocity(0, percent);
    } else {
      leftDrive.setVelocity(leftDriveVal, percent);
    }

    if(abs(rightDriveVal) < deadband){
      rightDrive.setVelocity(0, percent);
    } else {
      rightDrive.setVelocity(rightDriveVal, percent);
    }

    if(abs(frontDriveVal) < deadband){
      frontDrive.setVelocity(0, percent);
    } else {
      frontDrive.setVelocity(frontDriveVal, percent);
    }

    if(abs(rearDriveVal) < deadband){
      rearDrive.setVelocity(0, percent);
    } else {
      rearDrive.setVelocity(rearDriveVal, percent);
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
    leftDrive.spin(forward);
    rightDrive.spin(forward);
    frontDrive.spin(forward);
    rearDrive.spin(forward);
    grip.spin(forward);
  }
}
