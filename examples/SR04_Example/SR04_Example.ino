#include <Logging.h>
#include "SR04.h"

/*!
* This example use two SR04 ultrasonic devices and print the distance out
* on RS232
*
* Use my logging library too, for easy output
*
* This example use an Chip45 ATMega323p board. If you use an other Arduino
* please take care to use correct pins !
*
* Have fun
* mrRobot@web.de
*/


#define TRIGGER_PIN_US1 7
#define TRIGGER_PIN_US2 11

#define ECHO_PIN_US1 A2
#define ECHO_PIN_US2 A1

Logging logger = Logging(LOGLEVEL, 38400L);
SR04 sr04_1 = SR04(ECHO_PIN_US1, TRIGGER_PIN_US1);
SR04 sr04_2 = SR04(ECHO_PIN_US2, TRIGGER_PIN_US2);

// Pin PB2
#define LED_PIN 10

void setup() {
    pinMode(LED_PIN, OUTPUT);
    logger.Init();
    logger.Info(CR"******************************************"CR);
    logger.Info("Ultraschall - TEST SR04"CR);
    logger.Info("******************************************"CR);

}

void loop() {
	//doQuickPing();
	//doAvgDefaultPing();
	//doAvgMorePings(15,10);
	doAvgMorePings(15,20);
    delay(100);
    toggleLED(1, 50);
}

void doQuickPing() {
   long left,right;
	// get left distance in cm
    left = sr04_1.Distance();
	// get right distance in cm
    right = sr04_2.Distance();
    logger.Info("doQuickPing: Left/Right(%lcm/%lcm)"CR,
                left,right);
}

void doAvgDefaultPing() {
   long leftAvg,rightAvg;
	// get left average distance, use default parameter
    leftAvg = sr04_1.DistanceAvg();
	// get right averarge distance, use default parameter
    rightAvg = sr04_2.DistanceAvg();
    logger.Info(" doAvgDefaultPing: Left/Right(%lcm/%lcm)"CR,
                leftAvg, rightAvg);

}

/*!
* use DistanceAvg for measurment. Do not use default values
* 
* use 15ms delay per ping
* use 10pings
*/
void doAvgMorePings(int wait, int pings) {
   long leftAvg,rightAvg;
	// get left average distance
    leftAvg = sr04_1.DistanceAvg(wait,pings);
	// get right averarge distance
    rightAvg = sr04_2.DistanceAvg(wait,pings);
    logger.Info(" doAvgMorePings: delay %d, pings %d, Left/Right(%lcm/%lcm)"CR,
				wait,pings,
                leftAvg, rightAvg);

}

/**
* Blink on board led (on PB2)
* \param count number of blinks
* \param ms delay between blink
* Return:
*/
void toggleLED(byte count, int ms) {
    for (int x = 0; x < count; x++) {
        digitalWrite(LED_PIN, LOW);
        delay(ms);
        digitalWrite(LED_PIN, HIGH);
        delay(ms);
    }
}