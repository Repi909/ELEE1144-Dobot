#include "Dobot.h"
#include "irSensor.h"

Dobot dobot = Dobot();

void setup(){
  dobot.init();
}

void loop(){
  if(dobot.blockPresent){
    dobot.load();
  }
  else{
    if(Serial.available()){
      int readMsg = Serial.read()
      if(readMsg!=''){
        int msgNum = readMsg.toInt();
        dobot.unload(msgNum);
      }
    }
    else{
      Serial.println("Zzzzzz...");
    }
  }
}
