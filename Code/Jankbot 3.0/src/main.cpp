#include <Arduino.h>
#include <Stepper.h>
#define RPM 100
#define LOGPIN 15
#define STARTBTN 2
#define STEP_DISTANCE 0.16

bool start = false;
bool logIsThere = false;
volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

Stepper rightStepper(200,13,12,14,27);

Stepper leftStepper(200,26,25,33,32);

TaskHandle_t logAlign;

void moveStraight(int steps){
  rightStepper.step(steps);
  leftStepper.step(steps);
}

void IRAM_ATTR onTimer(){
  ESP.restart();
}

void logAlignTask(void * parameter){
  while(true){

  }
}

void setup() {
  rightStepper.setSpeed(RPM);
  leftStepper.setSpeed(RPM);
  pinMode(LOGPIN, INPUT);
  pinMode(STARTBTN, INPUT);

  while(!start){
    if(digitalRead(STARTBTN)){
      start = true;
    }
  }

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 240000000, true);
  timerAlarmEnable(timer);

  xTaskCreatePinnedToCore(
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
  while(!logIsThere){
    if(digitalRead(LOGPIN)){
      logIsThere = true;
      //TODO: move to build platform
    }
  }
  while(logIsThere){
    if(!digitalRead(LOGPIN)){
      logIsThere = false;
      delay(500); // Wait for claw to fully clear bot before moving away
      //TODO: move to river
    }
  }
}