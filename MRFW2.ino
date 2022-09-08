#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <NewPing.h>

#define TRIG A5
#define ECHO A4
#define MAX_DISTANCE 200

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for X axis motor
#define RPM 100

// X motor
#define DIR_R 4
#define STEP_R 3

// Y motor
#define DIR_L 6
#define STEP_L 5

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

#define LED 9

void moveForward();
void moveBack();
void turnLeft();
void turnRight();
void stop();
int readPing();
int lookLeft();
int lookRight();
void blink();

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
BasicStepperDriver R(MOTOR_STEPS, DIR_R, STEP_R);
BasicStepperDriver L(MOTOR_STEPS, DIR_L, STEP_L);
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick
// MultiDriver controller(R, L);
// OR
// synchronized move, trajectory is a straight line
SyncDriver controller(R, L);

void setup() {
    pinMode(LED, OUTPUT);

    R.begin(RPM, MICROSTEPS);
    L.begin(RPM, MICROSTEPS);

    Serial.begin(9600);

    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);

    blink();

    moveForward();
    moveBack();
    turnLeft();
    turnRight();
    stop();
}


void loop() {
    int distanceR = 0;
    int distanceL =  0;

    if (distance<=15) {
        stop(); 
        delay(500);
        //Serial.println("BACK");
        moveBack();
        stop();
        delay(500);
        //Serial.println("LOOK RIGHT");
        distanceR = lookRight();
        delay(500);
        //Serial.println("LOOK LEFT");
        distanceL = lookLeft();

        if (distanceR >= distanceL){
            //Serial.println("RIGHT");
            turnRight();
            stop();
        }
        else{
            //Serial.println("LEFT");
            turnLeft();
            stop();
        }
    }

    else {
        //Serial.println("FORWARD");
        moveForward();
    }

    distance = readPing();
}

void moveForward() {
    controller.rotate(90, 90);
}

void moveBack(){
    controller.rotate(-90, -90);
}

void turnLeft(){
    controller.rotate(90, -90);
}

int lookLeft(){
    controller.rotate(90, -90);
    delay(500);
    int distance = readPing();
    delay(100);
    controller.rotate(-90, 90);
    return distance;
    delay(100);
}

void turnRight(){
    controller.rotate(-90, 90);
}

int lookRight(){
    controller.rotate(-90, 90);
    delay(500);
    int distance = readPing();
    delay(100);
    controller.rotate(90, -90);
    return distance;
    delay(100);
}

void stop(){
    controller.startBrake();
}

int readPing() {
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void blink(){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(1000);
}

