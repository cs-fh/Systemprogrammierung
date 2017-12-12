
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
//#ifndef h
//#define h b
#include "speicherverwaltung/speicherverwaltung.h"
//#endif
#include "ledbar.h"

/**
 *\brief Stellt den Fuellstand des Heaps dar, wo jeder Block von einer LED auf der LED-Bar repraesentiert wird. 
 \return Anzahl der belegten Speicherbloecke
*/
int display_absolute(void);

/**
 *\brief Stellt den Fuellstand des Heaps prozentual auf der LED-Bar dar.
 \return Anzahl der leuchtenden LEDs
*/
int display_relative(void);

#ifdef __cplusplus
}
#endif
