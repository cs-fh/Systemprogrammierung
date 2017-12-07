
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <math.h>
#include "ledbar.h"
#include "speicherverwaltung.h"
#include "display.h"

int main ()
{


ten_blocks();
    for (int z = 0; z < 9; z++) {
        cm_malloc(111);
    }
display_relative();



}

