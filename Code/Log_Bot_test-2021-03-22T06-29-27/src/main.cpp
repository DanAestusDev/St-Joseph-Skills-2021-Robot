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
motor lift = motor(PORT15, ratio6_1,false);
motor turntable = motor(PORT16, ratio18_1, false);
motor grip = motor(PORT17, ratio6_1, false);

controller Controller1 = controller(primary);

bool RemoteControlCodeEnabled = true;
bool sideMotorsNeedStop = true;
bool mainMotorsNeedStop = true;

char pattern[] = {'.'};

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
while(true){
    if(RemoteControlCodeEnabled){
        int ch1Val = Controller1.Axis1.position();
        int ch2Val = Controller1.Axis2.position();
        int ch3Val = Controller1.Axis3.position();
        int ch4Val = Controller1.Axis4.position();
        if(mainMotorsNeedStop){
          leftDrive.stop();
          rightDrive.stop();
          mainMotorsNeedStop = false;
        }
        if(sideMotorsNeedStop){
          frontDrive.stop();
          rearDrive.stop();
          sideMotorsNeedStop = false;
        }

        if(abs(ch2Val) > 5){
          leftDrive.setVelocity(ch2Val, percent);
          rightDrive.setVelocity(ch2Val, percent);
          leftDrive.spin(forward);
          rightDrive.spin(forward);
          mainMotorsNeedStop = false;
        }

        if (abs(ch1Val) > 5){
          frontDrive.setVelocity(ch1Val, percent);
          rearDrive.setVelocity(ch1Val, percent);
          frontDrive.spin(forward);
          rearDrive.spin(forward);
          sideMotorsNeedStop = false;
        }

        if (abs(ch4Val) > 5){
          frontDrive.setVelocity(ch4Val, percent);
          leftDrive.setVelocity(ch4Val, percent);
          rearDrive.setVelocity(ch4Val, percent);
          rightDrive.setVelocity(ch4Val, percent);
          frontDrive.spin(forward);
          rearDrive.spin(reverse);
          leftDrive.spin(forward);
          rightDrive.spin(reverse);
          sideMotorsNeedStop = false;
          mainMotorsNeedStop = false;
        } else if(abs(ch4Val) < 5){
          sideMotorsNeedStop = true;
          mainMotorsNeedStop = true;
          // frontDrive.stop();
          // rearDrive.stop();
          // leftDrive.stop();
          // rightDrive.stop();
        }
        if(abs(ch2Val) < 5){
          mainMotorsNeedStop = true;
          // leftDrive.stop();
          // rightDrive.stop();
        }
        if(abs(ch1Val) < 5){
          sideMotorsNeedStop = true;
          // frontDrive.stop();
          // rearDrive.stop();
        }


        // leftDrive.setVelocity(Controller1.Axis3.position(), percent);
        // leftDrive.spin(forward);

        // rightDrive.setVelocity(Controller1.Axis2.position(), percent);
        // rightDrive.spin(forward);

        // frontDrive.setVelocity(Controller1.Axis4.position() + (Controller1.Axis3.position() - abs(Controller1.Axis2.position())), percent);
        // frontDrive.spin(forward);

        // rearDrive.setVelocity(Controller1.Axis1.position() + (Controller1.Axis2.position() - abs(Controller1.Axis3.position())), percent);
        // rearDrive.spin(forward);
      // if(abs(Controller1.Axis3.position()-Controller1.Axis2.position())>20){
      //   frontDrive.setVelocity(Controller1.Axis3.position(),percent);
      //   frontDrive.spin(forward);
      //   rearDrive.setVelocity(Controller1.Axis2.position(),percent);
      //   rearDrive.spin(forward);
      // }
      if(Controller1.ButtonX.pressing()){
      turntable.rotateTo(90, degrees, false);
      Controller1.rumble(pattern);
      }
    }
    wait(20, msec);
  }
  
}
