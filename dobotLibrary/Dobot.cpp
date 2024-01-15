#include "Arduino.h"
#include "Dobot.h"
#include "SoftwareSerial.h"
#include "blockMap.h"
#include "irSensor.h"
#include "counter.h"


//Globals:
SoftwareSerial mySerial = SoftwareSerial(2,3);  //Rx, Tx
byte  getPose[] = {170,170,2,10,0,246};
byte incomingByte; //to collect the response from Dobot
byte message[100];  //longer than the longest possible message
int i;
//Union type makes converting from byte array to float easy:
union coord {
  byte cByte[4];
  float cFloat;
};

coord cart[4];  //position of the arm in cartesian coordinates
coord pol[4];  //position of the arm in polar coordinates

//  Empty Constructor
Dobot::Dobot(){
};

// Setup
void Dobot::begin(){

  //init serial comms to Dobot
  Serial.begin(115200);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  mySerial.begin(115200);  //Dobot baud rate

  //create counter object
  Counter counter;

  //execute safe procedure
  Dobot::makeSafe();
  Serial.print("Dobot initialised!\nPlease place a block in the loading bay.")
}

//loads a block in to a storage bay based on block type passed in as argument. Moves block from import bay
void Dobot::load(uint8_t blockType){
  
  // uint8_t blockType = irSensor::blockDetector();
  if(blockType < 100){
    Serial.println("Loading...");
    if(blockType == 0){
      Dobot::move(30,1) //import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.whiteValue); //bay 0
      Dobot::suckStop();
      counter.whiteValue++;
    }
    else if(blockType == 10){
      Dobot::move(30,1) //import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.redValue); //bay 1
      Dobot::suckStop();
      counter.redValue++;
    }
    else{
      Dobot::move(30,1) //import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.blackValue); //bay 2
      Dobot::suckStop();
      counter.blackValue++;
    }
    Dobot::move(30,0);
    Serial.println("Loading complete!");
  }
  else{
    Serial.println("Zzzzzz...");
  }
}

//unloads a block from a storage bay specified in argument. Moves block to export bay
void Dobot::unload(uint8_t storageBay){
  if(storageBay < 4){
    Serial.Println("Unloading...");
    if(storageBay == 0){
      Dobot::move(0,counter.whiteValue);
      Dobot::suckStart();
      Dobot::move(30,2) //export bay
      Dobot::suckStop();
      counter.whiteValue--;
    }
    else if(storageBay == 1){
      Dobot::move(10,counter.redValue);
      Dobot::suckStart();
      Dobot::move(30,2) //export bay
      Dobot::suckStop();
      counter.redValue--;
    }
    else if(storageBay == 2){
      Dobot::move(20,counter.blackValue);
      Dobot::suckStart();
      Dobot::move(30,2) //export bay
      Dobot::suckStop();
      counter.blackValue--;
    }
    Dobot::move(30,0);
    Serial.println("Unloading complete!");
  }
  else{
    Serial.println("Invalid storage bay selected! Choose bay 0, 1 or 2.")
  }
}

//moves to positions of home, load, unload and 3 storage bays for visual checks by user.
void Dobot::makeSafe(){

  for(int i=0,i<3,i++){ 
    move(30,i);
  }
  for(int i=0,i<30,i++){ 
    move(i,0);
    i+=9;
  }
  move(30,0);
}

//move dobot arm to position specified in map by using blockType as multiple of 10 and counter for last block placed.
void Dobot::move(uint8_t blockType, uint8_t counter){

  vector<uint8_t> storageLocation = blockMap::accessValue(blockType, counter);
  for(int i=0;i<storageLocation.size();i++){
    mySerial.write(storageLocation[i]);
  }
}

//starts pump for suction
void Dobot::suckStart(){
  vector<uint8_t> suckStartPayload = blockMap::accessValue(30,3);
  for(int i=0; i<suckStartPayload.size(); i++){
    mySerial.write(suckStartPayload[i]);
  }
}

//stops pump for suction
void Dobot::suckStop(){
  vector<uint8_t> suckStopPayload = blockMap::accessValue(30,3);
  for(int i=0;i<suckStopPayload.size();i++){
    mySerial.write(suckStopPayload[i]);
  }
}

///////////////////////////////////////////ARCHIVED////////////////////////////////////////////////////////////////
//  Print Current Pose
// void  Dobot::printPose(){

// for(int i=0;i<6;i++){
//   mySerial.write(getPose[i]);
// }

// delay(50);  //allow time for the Dobot to serial send a response
// //Read response back from Dobot:
// i=0;
// while (mySerial.available() > 0){
//   message[i] = mySerial.read();
//   i++;
// }

// //distribute the Dobot position bytes to the appropriate coordinates:
// for(i=0;i<=3;i++){
//   cart[0].cByte[i] = message[i+5];
//   cart[1].cByte[i] = message[i+9];
//   cart[2].cByte[i] = message[i+13];
//   cart[3].cByte[i] = message[i+17];
//   pol[0].cByte[i] = message[i+21];
//   pol[1].cByte[i] = message[i+25];
//   pol[2].cByte[i] = message[i+29];
//   pol[3].cByte[i] = message[i+33];
// }
// Serial.print("Cartesian: ");
// Serial.print(cart[0].cFloat);  //The union type means the float equivalent is available
// Serial.print(" ");
// Serial.print(cart[1].cFloat);
// Serial.print(" ");
// Serial.print(cart[2].cFloat);
// Serial.print(" ");
// Serial.print(cart[3].cFloat);
// Serial.print(" Polar: ");
// Serial.print(pol[0].cFloat);
// Serial.print(" ");
// Serial.print(pol[1].cFloat);
// Serial.print(" ");
// Serial.print(pol[2].cFloat);
// Serial.print(" ");
// Serial.println(pol[3].cFloat);

// Serial.println("Full dobot message: ");
// for(int i=0; i<38; i++){
// Serial.print(message[i]);
// Serial.print(' ');
// }
// Serial.println();
// delay(1000);
// }

// void Dobot::commandFrame(byte comFrame[]){
  
// for(int i=0;i<(comFrame[2]+4);i++){   //The third comFrame byte gives the number of payload bytes; total number of bytes is 4 more than this
//   mySerial.write(comFrame[i]);
// }
// delay(50);

// //read response and send it to the serial monitor:
// Serial.print ("Dobot response:  ");
// while (mySerial.available() > 0){
//   message[0] = mySerial.read();
//   Serial.print(message[0]);
//   Serial.print(' ');
//   }
//   Serial.println();
// }