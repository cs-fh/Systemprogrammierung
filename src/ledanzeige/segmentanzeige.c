/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   segmentanzeige.c
 * Author: Nicola
 *
 * Created on 16. November 2017, 08:23
 */
#include "TM1637.c"
#include "ledanzeige/segmentanzeige.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
void TM1637_write_byte(byte wr_data){
    TM1637_display(SEG1, wr_data, OFF);
    
}

