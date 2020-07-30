#include "PositionController.h"
#include "LaserSatellite.h"
#include "RadioController.h"
#include <TinyGPS++.h>

TinyGPSPlus gps;

void startGPS(){
	delay(100);
	Serial1.begin(9600);
	delay(100);
	Serial1.print("$CCCAS,1,5*55\r\n");
	delay(100);
	Serial1.begin(115200);
	delay(100);
	Serial1.print("$CCINV,100,*60\r\n");
}

void updatePosition(){
	while (Serial1.available() > 0){
		gps.encode(Serial1.read());
}
if (gps.location.isUpdated()){
		gpsOK = true;
		pos.x = gps.location.lat()+offset.x;
		pos.y = gps.location.lng()+offset.y;
		pos.z = gps.altitude.meters()+offset.z;
		sendPos();
	}
}


void updateTarget(){
	if(gpsOK&&targetGpsOK&targetRadioOK){
	targetAngle = -atan2((targetPos.y-pos.y)*62500,(targetPos.x-pos.x)*112000)*57.2958;
	//}else{
	//  targetAngle = 0;
	}
}
