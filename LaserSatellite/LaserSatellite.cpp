#include "LaserSatellite.h"
#include "OrientationController.h"
#include "PositionController.h"
#include "MotorController.h"
#include "RadioController.h"
#include "SPI.h"


bool gpsOK = false;
bool targetGpsOK = false;
bool targetRadioOK = false;

Vector3 rot;
Vector3 pos;
Vector3 offset;
Vector3 targetPos;
float targetAngle = 0;

byte fps = 100;
unsigned long prevMicros = 0, deltaMicros = 0, currentMicros = 0;

int i = 0;

void setup(){
	#ifdef DEBUG_TO_SERIAL
	Serial.begin(115200);
	while(!Serial);
	Serial.println("Begin init...");
	#endif
	startIMU();
	startGPS();
	startRadio();
	startMotors();
	#ifdef DEBUG_TO_SERIAL
	Serial.println("Initialization completed");
	#endif
	prevMicros = micros();
}

void loop(){
	currentMicros = micros();
	deltaMicros = currentMicros - prevMicros;
	prevMicros = currentMicros;
	fps = 1000000 / deltaMicros;
	
	updateOrientation(fps);
	updatePosition();
	updateTarget();
	recieveRadio();
	setMotors(rot.z+targetAngle, rot.y);
	 
	i++;
	if(i==200){
		i = 0;
		#ifdef DEBUG_TO_SERIAL
		Serial.println("-----------------");
		Serial.println(targetPos.x*112000);
		Serial.println(targetPos.y*62500);
		Serial.println(targetPos.z);
		Serial.println(pos.x*112000);
		Serial.println(pos.y*62500);
		Serial.println(pos.z);
		#endif
	}
}
