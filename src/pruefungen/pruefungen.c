/*
 * pruefungen.c
 *
 * Alle Funktionen zur Pruefungsverwaltung sind in diesem Source File zu definieren.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "../include/pruefungen.h"
/*#include "../include/studiverwaltung.h"*/

student* exams[10];
const int MAXIMUM_POINTS = 320;

    int register_student(student *s, int nr) {
        int i;
        /*printf("MM%sMM", s); *s keinen zugriff :/ */
        if(s == NULL || nr < 0 || nr > 9) {
            return -1;
        }
        for(i = 0; i < 10; i++) {
            if(exams[i] == s) {
                return -1;
            }
        }
        i = 0;
        for(i = 0; i < 10; i++) {
            if(exams[nr] == NULL) {
                exams[nr] = s;
                return nr;
            }
            if(exams[nr] == s) {
                return -1;
            }
            if(nr == 9) {nr = 0;}
            else { nr++;}
        }
        return -1;
    }
    
    int remove_student(student *s) {
        int i;
        if(s == NULL) {
            return -1;
        }
        for( i = 0; i < 10; i++) {
            if(exams[i] == s) {
                exams[i] = NULL;
                return i;
            }
        }
        return -1;
    }
    
    void display_absolute() {
         brightness brt = OFF;
	init_led_bar();
        set_brightness(brt);
        brt = FULL;
	if(exams[LED01] != NULL) set_led(LED01, brt);
	if(exams[LED02] != NULL) set_led(LED02, brt);
	if(exams[LED03] != NULL) set_led(LED03, brt);
	if(exams[LED04] != NULL) set_led(LED04, brt);
	if(exams[LED05] != NULL) set_led(LED05, brt);
	if(exams[LED06] != NULL) set_led(LED06, brt);
	if(exams[LED07] != NULL) set_led(LED07, brt);
	if(exams[LED08] != NULL) set_led(LED08, brt);
	if(exams[LED09] != NULL) set_led(LED09, brt);
	if(exams[LED10] != NULL) set_led(LED10, brt);
    }

    int display_average(void) {
        float cpsges = 0.0, anz = 0.0, average = 0.0;
	int percentageint = 0, i = 0, nleds = 0;
	float percentage = 0.0;
	/*init_led_bar();*/
        for( i = 0; i < 10; i++) {
            if(exams[i] != NULL) {
                anz++;
                cpsges += exams[i]->cps;
            }
        }
        average = cpsges / anz;
	percentage = average / MAXIMUM_POINTS * 10;
	nleds = percentage; /*(float) average / MAXIMUM_POINTS * 10;*/
	percentageint =  percentage * 10;
	printf("%f %f - %d", average, percentage, nleds);
	/*for(i = 0; i < 10; i++) {
	    if(exams[i] != NULL) {
		
	    }
	}*/
        return percentageint;
    }


