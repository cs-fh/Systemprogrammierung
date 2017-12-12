/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   segmentanzeige.h
 * Author: Nicola
 *
 * Created on 16. November 2017, 08:37
 */

#ifndef SEGMENTANZEIGE_H
#define SEGMENTANZEIGE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;

typedef int segment;
enum Segmente {SEG1, SEG2, SEG3, SEG4};

typedef int dot;
const dot ON = 1;
const dot OFF = 0;

typedef int brightness;
const brightness DARK = 0;
const brightness MEDIUM = 1;
const brightness BRIGHT = 7;

void TM1637_write_byte(byte wr_data);

#ifdef __cplusplus
}
#endif



#endif /* SEGMENTANZEIGE_H */

