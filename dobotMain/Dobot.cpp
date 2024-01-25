#include "Arduino.h"
#include "ArduinoSTL.h"
#include "Dobot.h"
#include "SoftwareSerial.h"
//#include "blockMap.h"
#include "irSensor.h"
#include "counter.h"

// Globals:
SoftwareSerial mySerial(2, 3);  // Rx, Tx
byte getPose[] = {170, 170, 2, 10, 0, 246};
byte incomingByte;  // To collect the response from Dobot
byte message[100];  // Longer than the longest possible message
int i;

int bMap[35][23] = {
    //block type 0 (white)
    {170,170,19,84,3,0,0,0,25,67,0,0,24,67,0,0,79,194,0,0,0,0,225},
    {170,170,19,84,3,0,0,0,43,67,0,0,38,67,0,0,79,194,0,0,0,0,193},
    {170,170,19,84,3,0,0,0,64,67,0,0,53,67,0,0,79,194,0,0,0,0,157},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,79,194,0,0,0,0,122},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,79,194,0,0,0,0,86},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,210,193,0,0,0,0,212},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,210,193,0,0,0,0,248},
    {170,170,19,84,3,0,0,0,68,67,0,0,52,67,0,0,210,193,0,0,0,0,24},
    {170,170,19,84,3,0,0,0,48,67,0,0,38,67,0,0,210,193,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,31,67,0,0,25,67,0,0,210,193,0,0,0,0,88},
    
    //block type 1 (red)
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,79,194,0,0,0,0,8},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,79,194,0,0,0,0,18},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,79,194,0,0,0,0,199},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,79,194,0,0,0,0,39},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,79,194,0,0,0,0,177},
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,210,194,0,0,0,0,133},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,210,194,0,0,0,0,143},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,210,194,0,0,0,0,68},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,210,194,0,0,0,0,164},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,210,194,0,0,0,0,46},

    //block type 2(black)
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,79,194,0,0,0,0,172},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,79,194,0,0,0,0,130},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,79,194,0,0,0,0,95},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,79,194,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,79,194,0,0,0,0,32},
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,210,194,0,0,0,0,41},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,210,194,0,0,0,0,255},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,210,194,0,0,0,0,158},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,210,194,0,0,0,0,183},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,210,194,0,0,0,0,157},

    {170,170,19,84,3,0,0,0,52,67,0,0,0,0,0,0,0,0,0,0,0,50}, //home
    {170,170,19,84,3,0,0,0,255,65,0,0,125,67,0,0,79,194,0,0,0,0,152},  //import bay
    {170,170,19,84,3,0,0,0,8,66,0,0,149,195,0,0,81,194,0,0,0,0,244}// export bay
};

// Create counter object
Counter counter;

// Create blockmap object
//blockMap bMap;

// Empty Constructor
Dobot::Dobot() {
}

// Setup
void Dobot::begin() {

  // Init serial comms to Dobot
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  mySerial.begin(115200);  // Dobot baud rate

  // Execute safe procedure
  Dobot::makeSafe();
  Serial.println("Dobot initialised!\nPlease place a block in the loading bay.");
}

// Loads a block into a storage bay based on block type passed in as an argument. Moves block from import bay
void Dobot::load(uint8_t blockType) {

  // uint8_t blockType = irSensor::blockDetector();
  if (blockType < 100) {
    Serial.println("Loading...");
    if (blockType == 0) {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.whiteValue); // bay 0
      Dobot::suckStop();
      counter.whiteValue++;
    } else if (blockType == 10) {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.redValue); // bay 1
      Dobot::suckStop();
      counter.redValue++;
    } else {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.blackValue); // bay 2
      Dobot::suckStop();
      counter.blackValue++;
    }
    Dobot::move(30, 0);
    Serial.println("Loading complete!");
  } else {
    Serial.println("Zzzzzz...");
  }
}

// Unloads a block from a storage bay specified in the argument. Moves the block to the export bay
void Dobot::unload(uint8_t storageBay) {
  if (storageBay < 4) {
    Serial.println("Unloading...");
    if (storageBay == 0) {
      Dobot::move(0, counter.whiteValue);
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.whiteValue--;
    } else if (storageBay == 1) {
      Dobot::move(10, counter.redValue);
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.redValue--;
    } else if (storageBay == 2) {
      Dobot::move(20, counter.blackValue);
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.blackValue--;
    }
    Dobot::move(30, 0);
    Serial.println("Unloading complete!");
  } else {
    Serial.println("Invalid storage bay selected! Choose bay 0, 1, or 2.");
  }
}

//moves to positions of home, load, unload and 3 storage bays for visual checks by user.
void Dobot::makeSafe(){

  for(int i=0;i<3;i++){ 
    move(30,i);
  }
  for(int i=0;i<30;i++){ 
    move(i,0);
    i+=9;
  }
  move(30,0);
}

//move dobot arm to position specified in map by using blockType as multiple of 10 and counter for last block placed.
void Dobot::move(uint8_t blockType, uint8_t counter){

  int storageLocation[23]{bMap[blockType+counter]};
  for(int i=0;i<23;i++){
    mySerial.write(storageLocation[i]);
  }
}

//starts pump for suction
void Dobot::suckStart(){
  int suckStartPayload[]{170,170,4,62,1,1,1,191};
  for(int i=0; i<23; i++){
    mySerial.write(suckStartPayload[i]);
  }
}

//stops pump for suction
void Dobot::suckStop(){
  int suckStopPayload[23]{170,170,4,62,1,1,0,192};
  for(int i=0;i<23;i++){
    mySerial.write(suckStopPayload[i]);
  }
}

///////////////////////////////////////////ARCHIVED////////////////////////////////////////////////////////////////

// Union type makes converting from byte array to float easy:
// union coord {
//   byte cByte[4];
//   float cFloat;
// }

// coord cart[4];  // Position of the arm in cartesian coordinates
// coord pol[4];   // Position of the arm in polar coordinates
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
