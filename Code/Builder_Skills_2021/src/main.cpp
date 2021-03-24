/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Dan                                              */
/*    Created:      Mon Mar 22 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
controller vexRT = controller(primary);
motor leftDrive = motor(PORT1, ratio18_1,false);
motor rightDrive = motor(PORT2, ratio18_1,true);
motor xAxis = motor(PORT3, ratio18_1,false);
motor yAxis = motor(PORT4, ratio18_1,false);
motor zAxis = motor(PORT5, ratio18_1,false);
motor turnTable = motor(PORT6, ratio18_1,false);
motor rotator = motor(PORT7, ratio18_1,false);
motor claw = motor(PORT8, ratio18_1,false);

void driveMode();

void buildMode();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //minimum value of channels to prevent drift
  int deadband = 5;
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

    if (abs(leftSpeed) < 5){
      leftDrive.setVelocity(0,percent);
    } else {
      leftDrive.setVelocity(leftSpeed,percent);
    }

    if (abs(rightSpeed) < 5){
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
    if(vexRT.ButtonX.pressing()){
      while(vexRT.ButtonX.pressing()){
        if(!vexRT.ButtonX.pressing()){
          xAxis.stop();
          yAxis.stop();
          zAxis.stop();
          driveMode();
        }
      }
    }

    if(vexRT.ButtonUp.pressing()){
      xAxis.setVelocity(100, percent);
    } else if(vexRT.ButtonDown.pressing()){
      xAxis.setVelocity(-100, percent);
    } else {
      xAxis.setVelocity(0, percent);
    }

    if(vexRT.ButtonLeft.pressing()){
      yAxis.setVelocity(100, percent);
    } else if(vexRT.ButtonRight.pressing()){
      yAxis.setVelocity(-100, percent);
    } else {
      yAxis.setVelocity(0, percent);
    }

    if(vexRT.ButtonL1.pressing()){
      zAxis.setVelocity(100, percent);
    } else if(vexRT.ButtonL2.pressing()){
      zAxis.setVelocity(-100, percent);
    } else {
      zAxis.setVelocity(0, percent);
    }
    
    xAxis.spin(forward);
    yAxis.spin(forward);
    zAxis.spin(forward);

  }
}