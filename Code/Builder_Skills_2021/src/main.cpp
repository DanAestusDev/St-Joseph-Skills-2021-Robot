/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Dan                                              */
/*    Created:      Mon Mar 22 2021                                           */
/*    Description:  Skills 2021 builder bot                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
Control scheme:

Drive mode(starting mode):

Analog stick axes 2 and 3 control right and left drive motors respectively
Pretty much basic tank drive

X button switches to build mode

Build mode:

Right stick controls x and y movement 

Left stick axis 4 rotates the log using the rotator motor

Right shoulder buttons control z axis

Buttons Y and A open and close claw

Left shoulder buttons spin turntable

X button switches back to drive mode.

*/


#include "vex.h"

using namespace vex;
controller vexRT = controller(primary);
motor leftDrive = motor(PORT1, ratio18_1,false);
motor rightDrive = motor(PORT2, ratio18_1,true);
motor xAxis = motor(PORT3, ratio18_1,false);
motor xAxis2 = motor(PORT4, ratio18_1,true);
motor yAxis = motor(PORT5, ratio18_1,false);
motor zAxis = motor(PORT6, ratio18_1,false);
motor turnTable = motor(PORT7, ratio18_1,false);


void driveMode();

void buildMode();
//minimum value of channels to prevent drift
int deadband = 5;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  driveMode();

  
}

void driveMode(){
    while(true){
    if(vexRT.ButtonX.pressing()){
      while(vexRT.ButtonX.pressing()){
        if(!vexRT.ButtonX.pressing()){
          rightDrive.stop();
          leftDrive.stop();
          buildMode();
        }
      }
    }

    //Store values of controller joysticks
    int leftSpeed = vexRT.Axis3.position();
    int rightSpeed = vexRT.Axis2.position();

    if (abs(leftSpeed) < deadband){
      leftDrive.setVelocity(0,percent);
    } else {
      leftDrive.setVelocity(leftSpeed,percent);
    }

    if (abs(rightSpeed) < deadband){
      rightDrive.setVelocity(0,percent);
    } else {
      rightDrive.setVelocity(rightSpeed,percent);
    }

    leftDrive.spin(forward);
    rightDrive.spin(forward);

   }
}
void buildMode(){
  while(true){
    // check if x button is pressed; if so, stop all motors and switch to drive mode
    if(vexRT.ButtonX.pressing()){
      while(vexRT.ButtonX.pressing()){
        if(!vexRT.ButtonX.pressing()){
          xAxis.stop();
          yAxis.stop();
          zAxis.stop();
          turnTable.stop();
          rotator.stop();
          claw.stop();
          driveMode();
        }
      }
    }
    //retrieving joystick values

    int xSpeed =  vexRT.Axis2.position();
    int ySpeed = vexRT.Axis1.position();
    int logSpinSpeed = vexRT.Axis4.position();

    if (abs(xSpeed) < deadband){
      xAxis.setVelocity(0,percent);
      xAxis2.setVelocity(0,percent);
    } else {
      xAxis.setVelocity(xSpeed,percent);
      xAxis2.setVelocity(xSpeed,percent);
    }
    if (abs(ySpeed) < deadband){
      yAxis.setVelocity(0,percent);
    } else {
      yAxis.setVelocity(ySpeed,percent);
    }
    if (abs(logSpinSpeed) < deadband){
      rotator.setVelocity(0,percent);
    } else {
      rotator.setVelocity(ySpeed,percent);
    }

    if(vexRT.ButtonY.pressing()){
      claw.setVelocity(100, percent);
    } else if(vexRT.ButtonA.pressing()){
      claw.setVelocity(-100, percent);
    } else {
      claw.setVelocity(0, percent);
    }

    if(vexRT.ButtonR1.pressing()){
      zAxis.setVelocity(50, percent);
    } else if(vexRT.ButtonR2.pressing()){
      zAxis.setVelocity(-50, percent);
    } else {
      zAxis.setVelocity(0, percent);
    }
    if(vexRT.ButtonL1.pressing()){
      turnTable.setVelocity(50, percent);
    } else if(vexRT.ButtonL2.pressing()){
      turnTable.setVelocity(-50, percent);
    } else {
      turnTable.setVelocity(0, percent);
    }
    
    xAxis.spin(forward);
    yAxis.spin(forward);
    zAxis.spin(forward);
    rotator.spin(forward);
    claw.spin(forward);
    turnTable.spin(forward);
  }
}