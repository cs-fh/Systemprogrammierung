/*
 * tempSensor.cpp
 *
 */

/* **************************** VORGABEN ********************************** */
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h> // 3004 und 3008 sind wohl beide mit diesem zu nutzen.

#include "temperatur/tempSensor.h"


#define PIN_BASE 100
#define SPI_CHAN 0

TempSensor::TempSensor(float (*calcTempF)(int raw)) :
        fptr(calcTempF) {
    tempSensorInitialize();
}

float TempSensor::getTemp() {
    // get the raw output from the temperature sensor
    int raw = analogRead(PIN_BASE);

    return fptr(raw);
}

void TempSensor::tempSensorInitialize() {
    // initialize A/D with SPI channel and the PIN Base
    mcp3004Setup(PIN_BASE, SPI_CHAN);
}
/* **************************** VORGABEN ********************************** */

float f(int raw) {
		float temp = 0;
		std::cout << raw;
		temp = (((raw * 3.3) / 1024) - 0.5) * 100;
		return temp;
	}


