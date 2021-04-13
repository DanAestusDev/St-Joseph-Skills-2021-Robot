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

B button zeros out the carriage motor encoders

X button switches to build mode


Build mode:

Right stick controls x and y movement 

Left stick axis 4 rotates the log using the rotator motor

Right shoulder buttons control z axis

Buttons Y and A open and close claw

Left shoulder buttons spin turntable

Directional buttons move the carriage to predefined locations

B button zeros out the carriage motor encoders

X button switches back to drive mode.

*/


#include "vex.h"

using namespace vex;
controller vexRT = controller(primary);
motor leftDrive = motor(PORT1, ratio18_1,false);
motor rightDrive = motor(PORT2, ratio18_1,true);
motor xAxis = motor(PORT3, ratio6_1,false);
motor xAxis2 = motor(PORT4, ratio6_1,true);
motor yAxis = motor(PORT5, ratio6_1,false);
motor zAxis = motor(PORT6, ratio6_1,false);
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

    // Zero out carriage positions
    if(vexRT.ButtonB.pressing()){
      xAxis.resetRotation();
      xAxis2.resetRotation();
      yAxis.resetRotation();
      zAxis.resetRotation();
      turnTable.resetRotation();
    }

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

    
    // Zero out carriage positions
    if(vexRT.ButtonB.pressing()){
      xAxis.resetRotation();
      xAxis2.resetRotation();
      yAxis.resetRotation();
      zAxis.resetRotation();
      turnTable.resetRotation();
    }

    if (abs(xSpeed) < deadband){
      xAxis.setVelocity(0,percent);
      xAxis2.setVelocity(0,percent);
    } else {
      xAxis.setVelocity(xSpeed/3,percent);
      xAxis2.setVelocity(xSpeed/3,percent);
    }
    if (abs(ySpeed) < deadband){
      yAxis.setVelocity(0,percent);
    } else {
      yAxis.setVelocity(-ySpeed,percent);
    }

    if (abs(logSpinSpeed) < deadband){
      rotator.setVelocity(0,percent);
    } else {
      rotator.setVelocity(logSpinSpeed,percent);
    }

    if(vexRT.ButtonY.pressing()){
      claw.setVelocity(60, percent);
    } else if(vexRT.ButtonA.pressing()){
      claw.setVelocity(-60, percent);
    } else {
      claw.setVelocity(0, percent);
    }

    if(vexRT.ButtonR1.pressing()){
      zAxis.setVelocity(100, percent);
    } else if(vexRT.ButtonR2.pressing()){
      zAxis.setVelocity(-100, percent);
    } else {
      zAxis.setVelocity(0, percent);
    }

    if(vexRT.ButtonL1.pressing()){
      turnTable.setVelocity(20, percent);
    } else if(vexRT.ButtonL2.pressing()){
      turnTable.setVelocity(-20, percent);
    } else {
      turnTable.setVelocity(0, percent);
    }
    
    xAxis.spin(forward);
    xAxis2.spin(forward);
    yAxis.spin(forward);
    zAxis.spin(forward);
    rotator.spin(forward);
    claw.spin(forward);
    turnTable.spin(forward);

    //Autonomous carriage positions

    if(vexRT.ButtonUp.pressing()){
      xAxis.rotateTo(180, degrees,false);
      xAxis2.rotateTo(180, degrees,false);
      yAxis.rotateTo(2500, degrees, true);
      turnTable.rotateTo(-280,degrees,false);
    }
    if(vexRT.ButtonLeft.pressing()){
      xAxis.rotateTo(400, degrees, false);
      xAxis2.rotateTo(400, degrees, false);
      yAxis.rotateTo(5000, degrees, true);
      turnTable.rotateTo(0,degrees, false);
    }
    if(vexRT.ButtonDown.pressing()){
      xAxis.rotateTo(1800, degrees, false);
      xAxis2.rotateTo(1800, degrees, false);
      yAxis.rotateTo(2500, degrees, true);
      turnTable.rotateTo(-280,degrees, false);
    }
    if(vexRT.ButtonRight.pressing()){
      xAxis.rotateTo(400, degrees, false);
      xAxis2.rotateTo(400, degrees,false);
      yAxis.rotateTo(0, degrees, true);
      turnTable.rotateTo(0,degrees, false);
    }

    // software travel limits
    // if(xAxis.rotation(degrees)>1900){
    //   xAxis.rotateTo(1850, degrees);
    //   xAxis2.rotateTo(1850, degrees, true);
    // }
    // if(xAxis.rotation(degrees)<0){
    //   xAxis.rotateTo(0, degrees);
    //   xAxis2.rotateTo(0, degrees, true);
    // }
    // if(yAxis.rotation(degrees)>5100){
    //   yAxis.rotateTo(5100, degrees,true);
    // }
    // if(yAxis.rotation(degrees)<0){
    //   yAxis.rotateTo(0, degrees,true);
    // }
    // if(zAxis.rotation(degrees)>1000){
    //   zAxis.rotateTo(1000, degrees,true);
    // }
    // if(zAxis.rotation(degrees)<0){
    //   zAxis.rotateTo(0, degrees,true);
    // }
  }
}