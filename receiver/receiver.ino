// using libraries to communicate via the RF module --- *The SPI library is not used but is required by RH_ASK for compiling 
#include <RH_ASK.h>
#include <SPI.h>

// defining the input pins from the motor driver
#define md1 4 
#define md2 5 
#define md3 6 
#define md4 7

// making an object of RH_ASK class to use RF 
RH_ASK driver;

// a array of characters to store the final processed input
char receive[32];

// a variable to store time since the last input was received
unsigned long last = 0;

void setup()
{
  // defining the input pins from motor driver as output for arduino
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  pinMode(md3, OUTPUT);
  pinMode(md4, OUTPUT);
  
  // initiatating the driver object/ starting the communication
  driver.init();

  // initializing serial communication at baud rate of 9600 bits per second
  Serial.begin(9600);
  Serial.println("Started");

  // signalliing the motors to stop when starting - not needed but just to be safe
  stop();
}

void loop()
{
  // unsingned byte integer variables to store received input and its length
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  // checking for any values received via RF
  if (driver.recv(buf, &buflen))
  {
    // printing on serial monitor for testing
    Serial.print("receive: ");

    // storing the value of time when the input ws received
    last = millis();

    // replacing all the bits of 'receive' to 0
    memset(receive, 0, sizeof(receive));

    // storing the values recevied in 'receive'
    for (int i = 0; i < buflen; i++) 
    {
      receive[i] = buf[i];
    }
    Serial.println(receive);

    // comparing the received input with defined strings and when a match is found 
    // corresponding action is executed

    if (strcmp(receive, "forward") == 0) 
    {
      forward();
    }
    else if (strcmp(receive, "backward") == 0) 
    {
      reverse();
    }
    else if (strcmp(receive, "left") == 0) 
    {
      left();
    }
    else if (strcmp(receive, "right") == 0)
    {
      right();
    }
    else if (strcmp(receive, "stop") == 0) 
    {
      stop();
    }
  }
  
  // if no input received for 100 milliseconds stop the robot
  if ((millis() - last) >= 100) {
    stop();
  }
}

// function to move robot forward
void forward() 
{
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
  digitalWrite(md3, HIGH);
  digitalWrite(md4, LOW);
}

// function to move robot backwards
void reverse() 
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
  digitalWrite(md3, LOW);
  digitalWrite(md4, HIGH);
}

// function to move robot right
void right() 
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, HIGH);
  digitalWrite(md3, HIGH);
  digitalWrite(md4, LOW);
}

// function to move robot left
void left() 
{
  digitalWrite(md1, HIGH);
  digitalWrite(md2, LOW);
  digitalWrite(md3, LOW);
  digitalWrite(md4, HIGH);
}

// function to stop the robot
void stop() 
{
  digitalWrite(md1, LOW);
  digitalWrite(md2, LOW);
  digitalWrite(md3, LOW);
  digitalWrite(md4, LOW);
}