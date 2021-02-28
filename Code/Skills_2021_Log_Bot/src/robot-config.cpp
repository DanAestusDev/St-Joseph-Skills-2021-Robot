#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

motor leftDrive = motor(PORT11, ratio18_1, false);
motor rightDrive = motor(PORT12, ratio18_1, false);
motor frontDrive = motor(PORT13, ratio18_1, false);
motor rearDrive = motor(PORT14, ratio18_1, false);
motor armMotor = motor(PORT15, ratio18_1, false);
motor clawMotor = motor(PORT16, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      if(abs(Controller1.Axis3.position()) > 5){
        leftDrive.setVelocity(Controller1.Axis3.position(),percent);
        leftDrive.spin(forward);
      } else {
        leftDrive.stop();
      }
      if(abs(Controller1.Axis2.position()) > 5){
        rightDrive.setVelocity(Controller1.Axis2.position(),percent);
        rightDrive.spin(forward);
      } else {
        rightDrive.stop();
      }
      if(abs(Controller1.Axis4.position()) > 5){
        frontDrive.setVelocity(Controller1.Axis4.position(),percent);
        frontDrive.spin(forward);
      } else {
        frontDrive.stop();
      }
      if(abs(Controller1.Axis1.position()) > 5){
        rearDrive.setVelocity(Controller1.Axis1.position(),percent);
        rearDrive.spin(forward);
      } else {
        rearDrive.stop();
      }
      if(Controller1.ButtonR1.pressing()){
        armMotor.spin(forward);
      } else if(Controller1.ButtonR2.pressing()){
        armMotor.spin(reverse);
      } else{
        armMotor.stop();
      }
      if(Controller1.ButtonL1.pressing()){
        clawMotor.spin(forward);
      } else if(Controller1.ButtonL2.pressing()){
        clawMotor.spin(reverse);
      } else{
        clawMotor.stop();
      }
    }
    // wait before repeating the process
    wait(10, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}

      // // check the ButtonUp/ButtonDown status to control leftDrive
      // if (Controller1.ButtonUp.pressing()) {
      //   leftDrive.spin(forward);
      //   Controller1UpDownButtonsControlMotorsStopped = false;
      // } else if (Controller1.ButtonDown.pressing()) {
      //   leftDrive.spin(reverse);
      //   Controller1UpDownButtonsControlMotorsStopped = false;
      // } else if (!Controller1UpDownButtonsControlMotorsStopped) {
      //   leftDrive.stop();
      //   // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      //   Controller1UpDownButtonsControlMotorsStopped = true;
      // }