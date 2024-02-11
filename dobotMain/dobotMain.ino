#include "Dobot.h"
#include "irSensor.h"

//initialises dobot object
Dobot dobot = Dobot();

//setup dobot
void setup(){
  dobot.init();
  delay(10000);
}

void loop(){
  //checks if block is present
  if(dobot.blockPresent()){
    dobot.load();
    delay(5000);
  }
  //if no block, reads serial message
  else{
    String readMsg = Serial.readStringUntil('\n');
    readMsg.toLowerCase();
    //checks which block to unload if possible.
    if (readMsg != "clear"){
      int intMsg = readMsg.toInt();
      if(intMsg != 0){
        dobot.unload(intMsg);
      }
      else{
      Serial.println("Zzzzzz...");
      }
    }
    //if message clear, clears commands.
    else{
      dobot.ClearCommand();
    }
  }
  delay(2000);
}
