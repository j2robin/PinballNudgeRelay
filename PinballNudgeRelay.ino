/*
    MPU6050 based Pinball Nudge Relay.
    2022-12-31 by James R. Robinson (j2robin@gmail.com)

    Uses the MPU6050 library from Henrique Bruno Fantauzzi de Almeida which was forked from the original library from Korneliusz Jarzebski
    GIT: https://github.com/SrBrahma/Arduino-MPU6050
    
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const float XNUDGE_FORCE = .6;
const float YNUDGE_FORCE = .8;
const unsigned int TIME_BETWEEN_PRESSES = 400;
const unsigned int PRESS_DURATION = 100;
const unsigned int DLPF_MODE = 6;

unsigned long lastTime;
unsigned long currentTime;
bool leftNudge, rightNudge, forwardNudge;
int ON = 0, OFF = 1;
Vector normAccel, newAccel;

void setup() 
{
    //Setup the pins to be used for the relay outputs
    pinMode(4, OUTPUT); //Left Nudge
    pinMode(5, OUTPUT); //Right Nudge
    pinMode(6, OUTPUT); //Forward Nudge

    //Pulse the relays to initialize to a known state and give some information that the code is running :-)
    digitalWrite(4, ON);
    digitalWrite(5, ON);
    digitalWrite(6, ON);
    delay(500);
    digitalWrite(4, OFF);
    digitalWrite(5, OFF);
    digitalWrite(6, OFF);
    
    //Wait until the MPU6050 is up
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
    {
        delay(500);
    }
    
    mpu.resetDevice(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G); 

    mpu.calibrateAccelerometer();

    // Activate the low pass filter.  This is important to filter out things like vibrations from flipper force feedback and plunger use
    mpu.setDLPFMode(DLPF_MODE);

    currentTime = 0;
    lastTime = 0;
    leftNudge = false;
    rightNudge = false;
    forwardNudge = false;
}

void loop()
{

    normAccel.XAxis = 0;
    normAccel.YAxis = 0;
    normAccel.ZAxis = 0;

    newAccel = mpu.readNormalizedAccelerometer();

    normAccel.XAxis = newAccel.XAxis;
    normAccel.YAxis = newAccel.YAxis;
    normAccel.ZAxis = newAccel.ZAxis;

    currentTime = millis();

    //All nudges have a TIME_BETWEEN_PRESSES value to prevent buttons triggering in rapid succession which could reult in a tilt in game

    //Left Nudge
    if (normAccel.XAxis>XNUDGE_FORCE && ((currentTime-lastTime)>TIME_BETWEEN_PRESSES)) {
      if (!rightNudge) { //Don't trigger a left press if the right press is already happening
        digitalWrite(4, ON);
        leftNudge = true;
        lastTime = millis();
      }
    } else {
      if (leftNudge && (currentTime-lastTime > PRESS_DURATION)) { // Stop pressing the button after the appropiate time
        leftNudge = false;
        digitalWrite(4, OFF);
      }  
    }

    //Right Nudge
    if (normAccel.XAxis<(-1.0 * XNUDGE_FORCE) && ((currentTime-lastTime)>TIME_BETWEEN_PRESSES)) {
      if(!leftNudge) { //Don't trigger a right press if the left press is already happening
        digitalWrite(5, ON);
        rightNudge = true;
        lastTime = millis();
      }
    } else {
      if (rightNudge && (currentTime-lastTime > PRESS_DURATION)) { // Stop pressing the button after the appropiate time
        rightNudge = false;
        digitalWrite(5, OFF);
      }
    }

    //Trigger forward nudge from either forward or backward motion
    if ((normAccel.YAxis<(-1.0 * YNUDGE_FORCE))||(normAccel.YAxis>YNUDGE_FORCE) && ((currentTime-lastTime)>TIME_BETWEEN_PRESSES)) {
      digitalWrite(6, ON);
      forwardNudge = true;
      lastTime = millis();
    } else {
      if (forwardNudge && (currentTime-lastTime > PRESS_DURATION)) { // Stop pressing the button after the appropiate time
        forwardNudge = false;
        digitalWrite(6, OFF);
      }
    }

}