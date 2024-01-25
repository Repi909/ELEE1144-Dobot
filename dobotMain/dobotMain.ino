#include "Dobot.h"
#include "irSensor.h"
#include "Arduino.h"

Dobot dobot = Dobot();
char readMessage = -1;

void setup(){

  dobot.begin();
  delay(500);
}

int main(){
  if (Serial.available()){
     readMessage = Serial.read();
    if (dobot.blockPresent()){
      dobot.load(dobot.blockTypeDetector());
    }
    else if(readMessage==0|| readMessage==1||readMessage==2){
      dobot.unload(readMessage);
    }
    else{
      Serial.println("Zzzzzz...");
    }
    return 0;
  }
  else{
    return 0;
  }
}
