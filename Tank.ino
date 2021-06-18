#include <Wire.h>
#include <Adafruit_MotorShield.h>
 
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

 Adafruit_DCMotor *motorL = AFMS.getMotor(3);
 Adafruit_DCMotor *motorR = AFMS.getMotor(4);

int Speed = 0;


// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_ACCESS_PASSWORD "1234" // Here you can change the password or remove it


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,55,0,11,25,1,
  1,1,16,83,11,13,6,31,47,92,
  0,1,1,35,83,11,13,6,31,47,
  92,0,1,1,16,67,11,13,6,31,
  47,92,0,1,1,35,67,11,13,6,
  31,47,92,0,4,128,9,52,45,7,
  6,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t LeftBackward; // =1 if button pressed, else =0 
  uint8_t RightBackward; // =1 if button pressed, else =0 
  uint8_t LeftForward; // =1 if button pressed, else =0 
  uint8_t RightForward; // =1 if button pressed, else =0 
  int8_t MotorSpeed; // =0..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop) 

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 

  AFMS.begin();
  motorL->setSpeed(0);
  motorR->setSpeed(0); 
}


void loop() 
{ 
  RemoteXY_Handler ();


  Speed = map(RemoteXY.MotorSpeed, 0, 100, 0, 255); // Change the incoming slider value from 0-100 to 0-255
  motorL->setSpeed(Speed);
  motorR->setSpeed(Speed);


  if(RemoteXY.LeftBackward == 1){
    motorL->run(BACKWARD);
  }
  else{
    motorL->run(RELEASE);
  }

  if(RemoteXY.LeftForward == 1){
    motorL->run(FORWARD);
  }
  else{
    motorL->run(RELEASE);
  }


  if(RemoteXY.RightBackward == 1){
    motorR->run(BACKWARD);
  }
  else{
    motorR->run(RELEASE);
  }

  if(RemoteXY.RightForward == 1){
    motorR->run(FORWARD);
  }
  else{
    motorR->run(RELEASE);
  }
  
}
