/*
 * tempSensor.h
 *
 */

#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H


/* **************************** VORGABEN ********************************** */
class TempSensor {
public:
    TempSensor(float (*calcTempF)(int raw));
    float getTemp();

private:
    float (*fptr)(int raw);
    void tempSensorInitialize();
};
/* **************************** VORGABEN ********************************** */


float f(int raw);




#endif /* TEMPSENSOR_H */

