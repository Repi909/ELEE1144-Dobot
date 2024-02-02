#include "Dobot.h"
#include "irSensor.h"

Dobot dobot = Dobot(2,3);

void setup(){
  dobot.init();
}

void loop(){
  //CREATE STATE MACHINE
  if(dobot.blockPresent()){
    dobot.load();
  }
  else{
    if(Serial.available()){
      int8_t readMsg = Serial.read();
      if(readMsg != -1){
        dobot.unload(readMsg);
      }
    }
    else{
      Serial.println("Zzzzzz...");
    }
  }
}
