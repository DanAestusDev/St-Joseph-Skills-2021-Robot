#include <Arduino.h>
#include <Stepper.h>
#define RPM 200
#define LOGPIN 36
#define STARTBTN 37
#define INNERRIGHT 38
#define INNERLEFT 39
#define OUTERRIGHT 34
#define OUTERLEFT 35
#define STEP_DISTANCE 0.16
#define STEPS_PER_DEGREE 10.19

bool start = false;
bool logIsThere = false;
volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

Stepper rightStepper(200,13,12,14,27);

Stepper leftStepper(200,21,22,19,23);

Stepper logStepper(20,26,25,5,18);

TaskHandle_t logAlign;

// Move forward by a specified number of steps
void moveStraight(int steps){
  rightStepper.step(steps);
  leftStepper.step(steps);
}
//Rotate N amount of degrees, passed as an argument
void rotateNdegrees(int deg){
  leftStepper.step(round(deg*STEPS_PER_DEGREE));
  rightStepper.step(-round(deg*STEPS_PER_DEGREE));
}

// Reset bot after timer interrupt
void IRAM_ATTR onTimer(){
  Serial.print("Timer triggered, Restarting.../n");
  ESP.restart();
}

// Align log to center of tray
void logAlignTask(void * parameter){
  while(true){
     if((abs(analogRead(INNERLEFT))-abs(analogRead(INNERRIGHT))) >= 50 || (abs(analogRead(OUTERLEFT))-abs(analogRead(OUTERRIGHT))) >= 50 ){

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
      moveStraight(492);
      rotateNdegrees(-90);
      moveStraight(222);
      rotateNdegrees(90);
      moveStraight(250);
      rotateNdegrees(180);
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
      rotateNdegrees(-90);
      moveStraight(222);
      rotateNdegrees(90);
      moveStraight(492);
      rotateNdegrees(180);
      riverToPlatform();
    }
  }
}

void setup() {
  Serial.begin(115200);
  rightStepper.setSpeed(RPM); // Setting stepper speeds
  leftStepper.setSpeed(RPM);
  logStepper.setSpeed(RPM);
  pinMode(LOGPIN, INPUT); // Setting input pins for log presence detection and start btn
  pinMode(STARTBTN, INPUT);



  timer = timerBegin(0, 80, true); //Create timer
  timerAttachInterrupt(timer, &onTimer, true); // Attach interrupt function to timer
  timerAlarmWrite(timer, 240000000, true); // Set timer to fire after 240M microseconds (4 minutes)
  timerAlarmEnable(timer); // Start timer

  // xTaskCreatePinnedToCore( // Creating alignment task on core 0 to run concurrently to movement code
  //   logAlignTask,
  //   "logAlignTask",
  //   10000,
  //   NULL,
  //   0,
  //   &logAlign,
  //   0
  // );

  //TODO: Add code to move to start position
}

void loop() {
    while(!start){ // Wait for button activation
    if(!digitalRead(STARTBTN)){
      Serial.println("Started");
      start = true;
    }
  }
  riverToPlatform();
  // while(!logIsThere){ // When switch is not pressed (log not present)
  //   if(!digitalRead(LOGPIN)){ //On log drop event
  //     Serial.print("1st event");
  //     logIsThere = true; //log is present
  //     moveStraight(492);
  //     rotateNdegrees(-90);
  //     moveStraight(222);
  //     rotateNdegrees(90);
  //     moveStraight(250);
  //     rotateNdegrees(180);
  //   }
  // }
  // while(logIsThere){ // While switch is held down (log is present)
  //   if(digitalRead(LOGPIN)){ // On log lift event
  //     Serial.print("2nd event");
  //     logIsThere = false; // log is not present
  //     delay(500); // Wait for claw to fully clear bot before moving away
  //     moveStraight(250);
  //     rotateNdegrees(-90);
  //     moveStraight(222);
  //     rotateNdegrees(90);
  //     moveStraight(492);
  //     rotateNdegrees(180);
  //   }
  // }
}