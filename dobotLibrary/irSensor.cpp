#include "Arduino.h"
#include "irSensor.h"

uint8_t readSensor(){
    uint8_t avgSensorValue;
    for (int i =0, i< 101, i++){
        avgSensorValue += analogRead(A0);
    }
    return avgSensorValue/100;
}

uint8_t blockTypeCheck(uint8_t avgSensorValue){
    
    if(760 < avgSensorValue < 770){
        return 0;
    }

    else if (805 < avgSensorValue < 815){
        return 1;
    }

    else if(875 < avgSensorValue < 885){
        return 2;
    }

    else{
        Serial.Println("Invalid Part. Please speak to depot manager.")
    }
}

uint8_t blockDetector(){
    return blockTypeCheck(readSensor());
}