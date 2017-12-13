/*
 * ledbar.h
 *
 * Alle Funktionen, Strukturen und Konstanten zur LED-Bar sind in diesem
 * Header File zu deklarieren.
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;


#ifndef enums
#define enums
typedef enum leds {LED01, LED02, LED03, LED04, LED05, LED06, LED07, LED08, LED09, LED10} leds;
typedef enum brightness {FULL = 0xFF, MED = 0x0F, OFF = 0x00} brightness;
#endif


/**
*\brief Stellt Verbindung mit LED-Bar her.
*/
void init_led_bar(void);

/**
*\brief Stellt eine spezifizierte LED auf die uebergebene Helligkeit.
*\param led LED, dessen Helligkeit geaendert werden soll
*\param brt Die Helligkeit, die alle LEDs annehmen sollen
*\return Gibt 1 bei Erfolg, 0 bei Fehlschlag zurueck
*/
int set_led( leds led,  brightness brt);

/**
*\brief Gibt die Helligkeit einer LED zurueck.
*\param led LED, dessen Helligkeit ermittelt werden soll
*\return Helligkeit einer LED
*/
 brightness get_led( leds led);

/**
*\brief Stellt alle LEDs auf die uebergebene Helligkeit.
*\param brt Die Helligkeit, die alle LEDs annehmen sollen
*\return Gibt 1 bei Erfolg, 0 bei Fehlschlag zurueck
*/
int set_brightness( brightness brt);

#ifdef __cplusplus
}
#endif