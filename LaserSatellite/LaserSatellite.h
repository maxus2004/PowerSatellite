/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

//#define DEBUG_TO_SERIAL

struct Vector3{
  float x,y,z;
};

extern bool gpsOK;
extern bool targetGpsOK;
extern bool targetRadioOK;

extern Vector3 rot;
extern Vector3 pos;
extern Vector3 targetPos;
extern Vector3 offset;
extern float targetAngle;

extern unsigned long prevMicros, deltaMicros, currentMicros;

extern int i;
 
void setup();

void loop();