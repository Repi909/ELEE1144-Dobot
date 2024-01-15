#include "Arduino.h"
#include "irSensor.h"

irSensor::irSensor(){};

bool irSensor::blockPresent(){
    
}

uint8_t irSensor::readSensor(){
    uint8_t avgSensorValue;
    for (int i =0, i< 101, i++){
        avgSensorValue += analogRead(A0);
    }
    return avgSensorValue/100;
}

//blockTypeCheck returns a numeric value in multiples of 10 as a maximum of 10 blocks for each type can be placed.
//number is used within blockMap to return position element.
uint8_t irSensor::blockTypeDetector(){
    
    uint8_t avgSensorValue = irSensor::readSensor();

    if(760 < avgSensorValue < 770){
        Serial.println("White block detected! Starting loading sequence...");
        return 0;
    }

    else if (805 < avgSensorValue < 815){
        Serial.println("Red block detected! Starting loading sequence...");
        return 10;
    }

    else if(875 < avgSensorValue < 885){
        Serial.println("Black block detected! Starting loading sequence...");
        return 20;
    }

    else{
        Serial.println("Invalid block detected!");
        return 100;
    }
}