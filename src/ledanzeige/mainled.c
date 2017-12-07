#define MY_HEADER "/home/pi/Desktop/p1/wiringPi/wiringPi/wiringPi.h"

#include MY_HEADER
/*#include "./src/ledbar.c"*/
#include "../include/ledbar.h"
/*#include <wiringPi.h>*/
int main ()
{
  init_led_bar();
  /*char y;*/
  enum brightness brt = OFF;
  set_brightness(brt);
  /*for(y = 0; y < 10; y++) {
    
    /*LED_Bar_Status[y] = 0x00;
    set_led(y, brt);
  }*/
  /*enum leds xled = LED02;
  enum brightness brt = FULL;*/
  for(;;) {
    /*set_led(xled, brt);
    //set_brightness(brt);*/
    brt = FULL;
    set_brightness(brt);
    /*for(y = 0; y < 10; y++) {
      /*LED_Bar_Status[y] = 0xFF;
        set_led(y, brt);
    }*/
    /*send_led_data();*/
    brt = OFF,
    delay(500);
    set_brightness(brt);
    /*for(y = 0; y < 10; y++) {
      /*LED_Bar_Status[y] = 0x00;
	set_led(y, brt);
    }*/
    /*send_led_data();*/
    delay(500);
  } 
}
