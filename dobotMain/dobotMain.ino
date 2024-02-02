#include "Dobot.h"
#include "irSensor.h"

Dobot dobot = Dobot();

void setup(){
  dobot.init();
  delay(10000);
}

void loop(){
  if(dobot.blockPresent()){
    dobot.load();
  }
  else{
    if(Serial.available()){
      int readMsg = Serial.read();
      if(readMsg != -1){
        dobot.unload(readMsg);
      }
    }
    else{
      Serial.println("Zzzzzz...");
    }
  }
}
