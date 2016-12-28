const int ledNumber = 10;
char leds[ledNumber];
const char firstLed = 1;

void setup()
{
  for(char ledIncrement = 0;ledIncrement < ledNumber;ledIncrement++)
  {
    leds[ledIncrement] = firstLed+ledIncrement;
    pinMode(leds[ledIncrement], OUTPUT);
  }
}

void loop()
{
  lightWholeLedsArray(leds,ledNumber);
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

