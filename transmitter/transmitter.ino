// using libraries to communicate via the RF module --- *The SPI library is not used but is required by RH_ASK for compiling 
#include <RH_ASK.h>
#include <SPI.h>

// defining the input pins from which joytcick is connected
#define Jx A0
#define Jy A1

// defining variables to store values from the joystick module
int readX, readY;

// a pointer type character variable which will point towards the characters to be sent via RF transmitter
char *msg;

// making an object of RH_ASK class to use RF
RH_ASK driver;

void setup() 
{
  // defining the input pins from joystick module as input for arduino
  pinMode(Jx, INPUT);
  pinMode(Jy, INPUT);
  
  // initiatating the driver object/ starting the communication
  driver.init();

  // initializing serial communication at baud rate of 9600 bits per second
  Serial.begin(9600);

  // reading values from joytick when the arduino is powered on
  readJoystick();
}

void loop() 
{
  // specifying different actions based on different values from the joystick

  // when the joystick is in upwards direction the message sent is "forward"
  while (readY > 800) 
  {
    msg = "forward";
    transmit(msg);
    printTest(msg);
    readJoystick();
  }
  
  // when the joystick is in downwards direction the message sent is "backward"
  while (readY < 200) {
    msg = "backward";
    transmit(msg);
    printTest(msg);
    readJoystick();
  }

  // when the joystick is in left direction the message sent is "left"
  while (readX > 800) {
    msg = "left";
    transmit(msg);
    printTest(msg);
    readJoystick();
  }

  // when the joystick is in right direction the message sent is "right"
  while (readX < 200) {
    msg = "right";  
    transmit(msg);
    printTest(msg);
    readJoystick();
  }

  // when the joystick is in the moddle or it is just a little bit tilted in any direction the message sent is "stop"
  while (readX > 200 && readX < 800 && readY > 200 && readY < 800) {
    msg = "stop";
    transmit(msg);
    printTest(msg);
    readJoystick();
  }
}

// a function to transmit the array of characters sent in the parameter and then wait until the message is sent completely
void transmit(char *msg) {
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
}

// a function to read x and y values from the joystick module and storing those in global variables readX and readY respectively
void readJoystick()
{
  readX = analogRead(Jx);
  readY = analogRead(Jy);
}

// a function to print the message sent on the serial monitor (for testing)
void printTest(char* msg)
{
  Serial.print("Transmit: ");
  Serial.println(msg);
}