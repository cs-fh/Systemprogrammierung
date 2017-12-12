/*
 * ledbar.c
 *
 * Alle Funktionen zur LED-Bar sind in diesem Source File zu definieren.
 *
 */
#define MY_HEADER "/home/pi/wiringPi/wiringPi/wiringPi.h"

#include MY_HEADER

#include "ledanzeige/ledbar.h"

/* **************************** VORGABEN ********************************** */
/* Defines der Pins */
#define PIN_DATA 16         /* auf dem Shield PIN 15 */
#define PIN_CLOCK 27        /* auf dem Shield PIN 16 */
/* **************************** VORGABEN ********************************** */

static void latch_led_data(void);
static void toggle_clock(void);

/*typedef unsigned char byte;
static byte LED_Bar_Status[10];

enum leds {LED01, LED02, LED03, LED04, LED05, LED06, LED07, LED08, LED09, LED10};
enum brightness {FULL = 0xFF, MED = 0x0F, OFF = 0x00};*/

static byte LED_Bar_Status[10];
static void send_byte(byte b);


/* **************************** VORGABEN ********************************** */
/* Werte fuer Steuerregister */
static const byte REGISTER1 = 0x00;
static const byte REGISTER2 = 0x00;
static const byte EMPTY = 0x00;

/* Initialisierung der LED-Bar */
/*! \brief Die vorgegebene Funktion init_led_bar
 * Initialisierung der LED-Bar
 */
void init_led_bar(void) {
    static int device_initialised = 0;

    if (!device_initialised) {
        /* WiringPi initialisieren*/
        wiringPiSetup();

        /* Pins initialisieren*/
        pinMode(PIN_DATA, OUTPUT);
        pinMode(PIN_CLOCK, OUTPUT);
        digitalWrite(PIN_DATA, LOW);
        digitalWrite(PIN_CLOCK, LOW);

        /* Initialisierung nicht mehrfach durchfuehren*/
        device_initialised = 1;
    }
}

/* Senden der Daten an die LED-Bar */
/*! \brief Die vorgegebene Funktion send_led_data
 *  Senden der Daten an die LED-Bar
 */
static void send_led_data(void) { /*eig static?*/
    int i = 0;

    delayMicroseconds(250);

    /* Steuerregister setzen*/
    send_byte(REGISTER1);
    send_byte(REGISTER2);

    /* LED-Daten senden*/
    for (i = 0; i < 10; i++) {
        send_byte(EMPTY);
        send_byte(LED_Bar_Status[i]);
    }

    /* restliche Bytes senden*/
    for (i = 0; i < 4; i++) {
        send_byte(EMPTY);
    }

    /* Datenuebertragung abschliessen*/
    latch_led_data();
}

/* Clock-Pin togglen */
/*! \brief Die vorgegebene Funktion toggle_clock
 * Clock-Pin togglen
 */
static void toggle_clock(void) {
    static int clock_pin_active = 0;

    if (clock_pin_active) {
        digitalWrite(PIN_CLOCK, LOW);
        clock_pin_active = 0;
    } else {
        digitalWrite(PIN_CLOCK, HIGH);
        clock_pin_active = 1;
    }
}

/* Abschliessen der Datenuebertragung an die LED-Bar */
/*! \brief Die vorgegebene Funktion latch_led_data
 * Abschliessen der Datenuebertragung an die LED-Bar
 */
static void latch_led_data(void) {
    int i;

    digitalWrite(PIN_DATA, LOW);
    delayMicroseconds(250);

    for (i = 0; i < 4; i++) {
        digitalWrite(PIN_DATA, HIGH);
        delayMicroseconds(1);
        digitalWrite(PIN_DATA, LOW);
        delayMicroseconds(1);
    }

    delayMicroseconds(250);
    digitalWrite(PIN_CLOCK, LOW);
}
/* **************************** VORGABEN ********************************** */
/*! \brief Die Funktion send_byte
 *	Die Funktion arbeitet den übergebenen Parameter bitweise ab.
 * Dabei wird in einer Schleife jedes Mal eine '1' mit einer Bitstelle verundet.
 * Das sorgt dafür, dass immer eine Maske auf genau die Bitstelle gelegt wird, an welcher
 * sich die 1 auch gerade befindet, da die 1 in der Schleife immer um i Bitstellen verschoben wird.
 * \param b Zahl die übertragen werden soll
 */
static void send_byte(byte b) {
  char i;
  for(i = 0; i < 8; i++) {
    if(b & 0x0F) {
      digitalWrite(PIN_DATA, HIGH);
    } else {
      digitalWrite(PIN_DATA, LOW);
    }
    delayMicroseconds(10); /*Mirco*/
    toggle_clock();
    b = b << 1;
  }
}

/*! \brief Die Funktion set_led
 * Diese Funktion setzt an der Stelle led in der LED_Bar_Status den Helligkeitswert brt.
 * Falls led kleiner als 0 oder grösser als 9 ist, wird 0 zurückgegeben.
 * \param led Stelle an der LED-Bar, welche verändert werden soll
 * \param brt Helligkeitswert für die Stelle led
 * \return Entweder '1' bei erfolgreichen Setzen des Helligkeitswert, oder '0' bei einem Fehlschlag
 */
int set_led( leds led,  brightness brt) {
  if(!led || !brt) {
    return 0;
  }
  LED_Bar_Status[led] = brt;
  send_led_data();
  return 1;
}

 /*! \brief Die Funktion get_led
 * Eine einfache Getter-Funktion, die an der Stelle led, den Helligkeitswert ausgibt
 * \param led Welche LED ausgegeben werden soll.
 * \return Helligkeitswert der ausgegeben werden soll
 */
 brightness get_led( leds led) {
  if(LED_Bar_Status[led] == OFF) {
     return OFF;
  }
  else if(LED_Bar_Status[led] == MED) {
    return MED;
  } else {
      /*byte i = LED_Bar_Status[led]*/
  return FULL;
  }
}

/*! \brief Die Funktion set_brightness
 * Die Funktion setzt für alle LEDs den Helligkeitswert brt.
 * Dieser kann entweder FULL, MED oder OFF sein.
 * Falls der Helligkeitswert nicht FULL, MED oder OFF entspricht, wird
 * 0 zurückgegeben.
 * \param brt Helligkeitswert für die gesamte LED-Bar
 * \return Entweder '1' bei erfolgreichen Setzen des Helligkeitswert, oder '0' bei einem Fehlschlag
 */
int set_brightness( brightness brt) {
  int i;
  if(!brt) return 0;
  for(i = 0; i < 10; i++) {
    LED_Bar_Status[i] = brt;
  }
  send_led_data();
  return 1;
}



