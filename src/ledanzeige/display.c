
#include "ledanzeige/display.h"

int display_absolute(void) {
    memblock *curr;
    int nleds = 0; leds sht = LED01;
    curr = (memblock*) mempool;

    init_led_bar();
    set_brightness(OFF);

    while(curr != NULL) {
		if(curr->next == (memblock*) MAGIC_INT) {
			nleds += 1;
			set_led(sht, FULL);
		}
	
		if( ( ((char*)curr) + (curr->size + sizeof(memblock))) < (mempool + MEM_POOL_SIZE - 1) )
			curr = (memblock*)( ((char*)curr) + (curr->size + sizeof(memblock)));
		else curr = NULL;
		sht = sht+(enum leds)1;
    }
    return nleds;
}

int display_relative(void) {
    memblock *curr;
    size_t sum = 0;
    float percent = 0.0;
    int nleds = 0, number = 0;
    curr = (memblock*) mempool;

    init_led_bar();

    while(curr != NULL) {
		if(curr->next == (memblock*) MAGIC_INT) {
			sum += curr->size + sizeof(memblock);
		}

		if( ( ((char*)curr) + (curr->size + sizeof(memblock))) < (mempool + MEM_POOL_SIZE - 1) )
			curr = (memblock*)( ((char*)curr) + (curr->size + sizeof(memblock)));
		else curr = NULL;
    }
    
    percent = ((float) sum / MEM_POOL_SIZE) * 100;
    number = ceil(percent / 10);
	nleds = number; /*
if(0 < nleds && nleds <= 10) {set_led(LED01, FULL);}
else if(10 < nleds && nleds <= 20) {set_led(LED01, FULL); set_led(LED02, FULL);}
	else if(20 < nleds && nleds <= 30) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL);}
	else if(30 < nleds && nleds <= 40) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL);}
	else if(40 < nleds && nleds <= 50) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL);}
	else if(50 < nleds && nleds <= 60) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL);}
	else if(60 < nleds && nleds <= 70) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL);}
	else if(70 < nleds && nleds <= 80) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL);}
	else if(80 < nleds && nleds <= 90) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL); set_led(LED09, FULL);}
	else if(90 < nleds && nleds <= 100) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL); set_led(LED09, FULL); set_led(LED10, FULL); }
*/

	if(nleds == 1) {set_led(LED01, FULL);}
	if(nleds == 2) {set_led(LED01, FULL); set_led(LED02, FULL);}
	if(nleds == 3) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL);}
	if(nleds == 4) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL);}
	if(nleds == 5) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL);}
	if(nleds == 6) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL);}
	if(nleds == 7) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL);}
	if(nleds == 8) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL);}
	if(nleds == 9) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL); set_led(LED09, FULL);}
	if(nleds == 10) {set_led(LED01, FULL); set_led(LED02, FULL); set_led(LED03, FULL); set_led(LED04, FULL); set_led(LED05, FULL); set_led(LED06, FULL); set_led(LED07, FULL); set_led(LED08, FULL); set_led(LED09, FULL); set_led(LED10, FULL); }


    return number;
}
