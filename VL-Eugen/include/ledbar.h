/*
 * ledbar.h
 *
 * Alle Funktionen, Strukturen und Konstanten zur LED-Bar sind in diesem
 * Header File zu deklarieren.
 *
 */
 #ifndef LED_H
#define LED_H
 #ifdef __cplusplus
extern "C"{
#endif	
typedef unsigned char byte; /*!<Der Dateityp byte geht von 0 bis 255 */
extern byte LED_Bar_Status[10];
/*! \brief LEDs
 * Aufzählung von LEDs. Diese werden benötigt 
 * um die richtigen LEDs anzusprechen.
 */
typedef enum leds {
		LED01 = 0,
		LED02 = 1,
		LED03 = 2,
		LED04 = 3,
		LED05 = 4,
		LED06 = 5,
		LED07 = 6,
		LED08 = 7,
		LED09 = 8,
		LED10 = 9
} leds;
/*! \brief Helligkeitswerte
 * Aufzählung der Helligkeitswerte, welche für
 * die LEDs eingestellt werden können.
 */
typedef enum brightness {
	FULL=0xff, MED=0x0f, OFF=0x00
} brightness;
void init_led_bar(void);
void send_byte(byte b);
int set_led(leds led, brightness brt);
brightness get_led(leds led);
int set_brightness(brightness brt);
#ifdef __cplusplus
}
#endif
#endif /* LED_H */
