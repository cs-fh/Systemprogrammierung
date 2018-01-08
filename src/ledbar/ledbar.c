/*
 * ledbar.c
 *
 * Alle Funktionen zur LED-Bar sind in diesem Source File zu definieren.
 *
 */

#include <wiringPi.h>
#include "ledbar/ledbar.h"

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

int set_led( leds led,  brightness brt) {
  /*if(!led || !brt) {
    return 0;
  }*/
  LED_Bar_Status[led] = brt;
  send_led_data();
  return 1;
}

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

int set_brightness( brightness brt) {
  int i;
  /*if(!brt) return 0;*/
  for(i = 0; i < 10; i++) {
    LED_Bar_Status[i] = brt;
  }
  send_led_data();
  return 1;
}



