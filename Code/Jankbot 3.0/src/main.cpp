#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#define RPM 30
#define LOGPIN 33
#define STARTBTN 32
#define INNERRIGHT 39
#define INNERLEFT 36
#define OUTERRIGHT 35
#define OUTERLEFT 34
#define STEP_DISTANCE 0.16
#define STEPS_PER_DEGREE 1.23
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000


bool start = false;
bool logIsThere = false;
volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

BasicStepperDriver leftStepper(200, 13, 12);
BasicStepperDriver rightStepper(200, 14, 27);
BasicStepperDriver logStepper(20, 26, 25);

MultiDriver driveController(leftStepper, rightStepper);

TaskHandle_t logAlign;

// Move forward or reverse by a specified number of steps
void moveStraight(int steps){
  //leftStepper.move(steps);
  driveController.move(steps,steps);
}
//Rotate N amount of degrees, passed as an argument
void rotateNdegrees(int deg){
  driveController.move(round(deg*STEPS_PER_DEGREE),-(round(deg*STEPS_PER_DEGREE)));
}

// Reset bot after timer interrupt
void IRAM_ATTR onTimer(){
  Serial.print("Timer triggered, Stopping/n");
  while(true){
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

// Align log to center of tray
void logAlignTask(void * parameter){
  while(true){
     if((abs(analogRead(INNERLEFT))-abs(analogRead(INNERRIGHT))) >= 50 || (abs(analogRead(OUTERLEFT))-abs(analogRead(OUTERRIGHT))) >= 50 ){
       logStepper.move(1);
     }
    if((abs(analogRead(INNERRIGHT))-abs(analogRead(INNERLEFT))) >= 50 || (abs(analogRead(OUTERRIGHT))-abs(analogRead(OUTERLEFT))) >= 50 ){
       logStepper.move(-1);
     }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
void platformToRiver();

void riverToPlatform(){
    while(true){ // When switch is not pressed (log not present)
    if(!digitalRead(LOGPIN)){ //On log drop event
      Serial.println("1st event");
      logIsThere = true; //log is present
      delay(500);
      moveStraight(425);
      rotateNdegrees(-44);
      moveStraight(220);
      rotateNdegrees(-133);
      moveStraight(-260);
      //rotateNdegrees(180);
      platformToRiver();
    }
  }
}
void platformToRiver(){
  while(true){ // While switch is held down (log is present)
    if(digitalRead(LOGPIN)){ // On log lift event
      Serial.println("2nd event");
      logIsThere = false; // log is not present
      delay(500); // Wait for claw to fully clear bot before moving away
      moveStraight(250);
      rotateNdegrees(-44);
      moveStraight(220);
      rotateNdegrees(-133);
      moveStraight(-435);
      //rotateNdegrees(180);
      riverToPlatform();
    }
  }
}

void setup() {
  Serial.begin(115200);
  leftStepper.begin(RPM, 1);
  rightStepper.begin(RPM, 1);  
  pinMode(LOGPIN, INPUT); // Setting input pins for log presence detection and start btn
  pinMode(STARTBTN, INPUT);
  // leftStepper.setSpeedProfile(leftStepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  // rightStepper.setSpeedProfile(rightStepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
   while(!start){ // Wait for button activation
    if(!digitalRead(STARTBTN)){
      Serial.println("Started");
      start = true;
    }
  }

  timer = timerBegin(0, 80, true); //Create timer
  timerAttachInterrupt(timer, &onTimer, true); // Attach interrupt function to timer
  timerAlarmWrite(timer, 240000000, true); // Set timer to fire after 240M microseconds (4 minutes)
  timerAlarmEnable(timer); // Start timer

  xTaskCreatePinnedToCore( // Creating alignment task on core 0 to run concurrently to movement code
    logAlignTask,
    "logAlignTask",
    10000,
    NULL,
    0,
    &logAlign,
    0
  );

  //TODO: Add code to move to start position
}

void loop() {

  riverToPlatform();
 
}