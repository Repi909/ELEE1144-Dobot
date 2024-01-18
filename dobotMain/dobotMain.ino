#include "Dobot.h"
#include "irSensor.h"
#include "Arduino.h"

Dobot dobot = Dobot();

int setup(){

  dobot.begin();
  delay(500);
  return 0;
}

int main(){

  while(serial.available){

    if (irSensor::blockPresent()){
      dobot.load(irSensor::blockTypeDetector());
    }
    else if(Serial.read()==0|| serial.Read()==1||serial.Read()==2){
      dobot.unload();
    }
    else{
      Serial.println("Zzzzzz...");
    }
    return 0;
  }
}