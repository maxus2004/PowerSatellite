#include "RadioController.h"
#include "LaserSatellite.h"
#include <RF24.h>

RF24 radio(7,8);

unsigned long lastPacket = 0;

void startRadio(){
	radio.begin();
	radio.setAutoAck(false);
	radio.openReadingPipe(0, 0x1234567890LL);
	radio.openWritingPipe(0x1234567891LL);
	radio.setPALevel(RF24_PA_HIGH);
	radio.startListening();
}

void recieveRadio(){
	if(radio.available()){
		lastPacket = millis();
		targetRadioOK = true;
		radio.read(&targetPos,12);
		if(targetPos.z==-666){
			offset.x = targetPos.x;
			offset.y = targetPos.y;
			offset.z = 0;
		}
		if(targetPos.x==0){
			targetGpsOK = false;
			}else{
			targetGpsOK = true;
		}
	}
	if(millis() - lastPacket > 500){
		targetRadioOK = false;
	}
}

void sendPos(){
	radio.stopListening();
	radio.write(&pos,12);
	radio.startListening();
}
