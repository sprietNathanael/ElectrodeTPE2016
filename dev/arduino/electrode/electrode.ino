#include <Servo.h>

const int ledNumber = 9;
char leds[ledNumber];
const char firstLed = 3;
const int maxAnalogValue = 1023;
int analogValue = 0;
const char analogPin = 0;
Servo servomotor;
int servoPin = 12;
int val = 0;

void setup()
{
  for(char ledIncrement = 0;ledIncrement < ledNumber;ledIncrement++)
  {
    leds[ledIncrement] = firstLed+ledIncrement;
    pinMode(leds[ledIncrement], OUTPUT);
  }
  servomotor.attach(servoPin);
}

void loop()
{
  //lightWholeLedsArray(leds,ledNumber);  
  val = analogRead(analogPin);
  lightSomeOfLedsArray(leds, ledNumber, intToNumberOfLedsToLight(val,ledNumber));
  intToServo(val);
  
}

void lightWholeLedsArray(char *ledsArray, int arraySize)
{
  lightSomeOfLedsArray(ledsArray,arraySize,ledNumber);
}

void lightSomeOfLedsArray(char *ledsArray, int arraySize, int numberOfLedsToLight)
{
  if(numberOfLedsToLight > arraySize)
  {
    numberOfLedsToLight = arraySize;
  }
  for(int i = 0; i < numberOfLedsToLight; i++)
  {
    digitalWrite(ledsArray[i], HIGH);
    delay(0.1);
    digitalWrite(ledsArray[i], LOW);
  }
}

int intToNumberOfLedsToLight(int valueToProcess, int ledQuantity)
{
  //int numberOfLedsToLight= ((100*valueToProcess)/maxAnalogValue)/ledQuantity;
  int numberOfLedsToLight = map(valueToProcess,0,1023,0,ledQuantity);
  return(numberOfLedsToLight);
}

void intToServo(int valueToProcess)
{
  int valueToWrite = map(valueToProcess, 0, 1023, 0, 180);
  servomotor.write(valueToWrite);
}
