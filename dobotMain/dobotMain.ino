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
    delay(5000);
  }
  else{
    String readMsg = Serial.readStringUntil('\n');
    readMsg.toLowerCase();
    if (readMsg != "clear"){
      int intMsg = readMsg.toInt();
      if(intMsg != 0){
        dobot.unload(intMsg);
      }
      else{
      Serial.println("Zzzzzz...");
      }
    }
    else{
      dobot.ClearCommand();
    }
  }
  delay(2000);
}
