/**
    electrode.ino

    Takes a 0-5V analog value from MyoWare electrode kit, and enlights a led bar
    and commands a Servo motor according to the read value

    The circuit:
    * A defined number of leds (9 in this example)
    * A 100 ohm resistor connected to the led common ground
    * A servo motor supplied with 5V

    Created by Nathanaël Spriet for the high school TPE of Robin Spriet.
**/


/****************** Librairies including **********************/
#include <Servo.h>

/****************** Constants **********************/

/*****Leds******/

// The number of leds
const int ledNumber = 10;

// An array of leds containing ledNumber entries
char leds[ledNumber];

// The pin number of the first led
const char firstLed = 2;

/*****Analog input******/

// The max analog value that can be read
const int maxAnalogValue = 1023;

// The read analog value
int analogValue = 0;

// The pin number of the analog input
const char analogPin = 0;

// The result of the low pass filter
int filtredVal = 0;

/*****Servo motor******/

// The Servo object for the servomotor
Servo servomotor;

// The pin number of the servomotor command
int servoPin = 11;


/****************** Main Functions **********************/

/**
 * Setup function of the Arduino Core
 * Initializes the different arrays and objects
 */
void setup()
{
    /**
     *  For loop that puts in each ledArray elements the pin number corresponding
     *  and passes them into Output mode
     *  For example :
     *      * ledArray[0] will be 3 (the firstLed pin)
     *      * ledArray[4] will be 7 (the fifth led pin)
     */
    for(char ledIncrement = 0;ledIncrement < ledNumber;ledIncrement++)
    {
        leds[ledIncrement] = firstLed+ledIncrement;
        pinMode(leds[ledIncrement], OUTPUT);
    }

    // Ataches the servomotor pin number to the servomotor object
    servomotor.attach(servoPin);
}

/**
 * Loop function of the Arduino
 * Loops indefinitely
 */
void loop()
{
    // Test to light all the leds
    //lightWholeLedsArray(leds,ledNumber);

    // Read the analog value
    analogValue = analogRead(analogPin);

    // Applies a low-pass filter : filtredValue = (readValue * a) + (b * previousFiltredValue)
    // with a+b = 1
    filtredVal = (int)((analogValue*0.1)+(0.9*filtredVal));
    //filtredVal = analogValue;

    // Lights the corresponding number of leds according to the analog value
    lightSomeOfLedsArray(leds, ledNumber, intToNumberOfLedsToLight(filtredVal,ledNumber));

    // Commands the servo motor according to the analog value
    intToServo(filtredVal);

}

/**
 * Lights the whole array of leds passed into parameter
 * @param ledsArray The array of leds
 * @param arraySize The size of the array
 */
void lightWholeLedsArray(char *ledsArray, int arraySize)
{
    // Just calls the lightSomeOfLedsArray function with ledNumber
    lightSomeOfLedsArray(ledsArray,arraySize,ledNumber);
}

/**
 * Lights some of the leds of the array passed into param
 * @param ledsArray           The array of leds
 * @param arraySize           The size of the array
 * @param numberOfLedsToLight The number of the leds to light
 */
void lightSomeOfLedsArray(char *ledsArray, int arraySize, int numberOfLedsToLight)
{
    // Checks if the numberOfLedsToLight is greater than the array size
    if(numberOfLedsToLight > arraySize)
    {
        // If it's greater, just replaces it by the array size
        numberOfLedsToLight = arraySize;
    }

    // For loop that goes from the first led to the numberOfLedsToLight
    for(int i = 0; i < numberOfLedsToLight; i++)
    {
        // Turns on the current led
        digitalWrite(ledsArray[i], HIGH);

        // Waits 100 microseconds
        delay(0.1);

        // Turns off the current led
        digitalWrite(ledsArray[i], LOW);
    }
}

/**
 * Computes the number of leds to light according to the analog read value
 * @param  valueToProcess The analog read value
 * @param  ledQuantity    The number of leds in the array
 * @return                The number of leds to light
 */
int intToNumberOfLedsToLight(int valueToProcess, int ledQuantity)
{
    // Old method
    //int numberOfLedsToLight= ((100*valueToProcess)/maxAnalogValue)/ledQuantity;

    /*
     New method, with map function
     The map function :
     * maps a value (first parameter)
     * that ranges from number1 (paramter2) to number2 (parameter3)
     * on a range from number3 (parameter4) to number 4 (parameter5)
     * and returns the result
     For example :
     * The value ranges from 0 to 20 and equals 10
     * The desired range is from 30 to 40
     * The result will be 35
     */

    // Maps the analog value that ranges from 0 to 1023 on a range from 0 to ledQuantity
    int numberOfLedsToLight = map(valueToProcess,0,1023,0,ledQuantity);


    return(numberOfLedsToLight);
}

/**
 * Commands the servo motor according to the analog read value
 * @param valueToProcess The analog read value
 */
void intToServo(int valueToProcess)
{
    // Computes the value to send with map function (for more details on map function,
    // see the intToNumberOfLedsToLight function)

    // Maps the analog value that ranges from 0 to 1023 on a range from 0 to 180
    int valueToWrite = map(valueToProcess, 0, 1023, 0, 180);

    // Commands the servomotor with the computed function
    servomotor.write(valueToWrite);
}
