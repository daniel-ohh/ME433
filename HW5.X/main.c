/* 
 * File:   main.c
 * Author: danieloh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include <math.h>
#include "NU433.h"
#include "spi.h"
#define NUMSAMPS 1000

int main() {
    initSPI();
    NU433setup(); 
    double sinwave[NUMSAMPS];
    double triangle[NUMSAMPS];
    
    int i;
    //making the waveforms, square has two cycles and triangle has 1
    double rad = 0;
    double pi = 3.142857;
    
    for (i=0;i<NUMSAMPS;i++) {
        //sine waveform will have two cycles in it
        rad = rad+4*pi/NUMSAMPS;
        sinwave[i] = 3.3/2*sin(rad)+3.3/2;
        
        //triangle waveform
        if (i<NUMSAMPS/2) {
            triangle[i] = 3.3/(NUMSAMPS/2) * i;
        }
        
        if (i>=NUMSAMPS/2) {
            triangle[i] = -3.3/(NUMSAMPS/2)*i + 6.6;
        }
    }
    
    //unsigned char c;
    unsigned short V_tri, V_sin, c;
    i = 0;
    
    while (1) {
        
        unsigned short p=0;
        //sin wave at DACA
        c = 0b1;
        V_sin = sinwave[i]/3.3*256;
        //V_sin=.5/3.3*256;
        p = p|(c<<15);
        p = p|(0b111<<12);
        p = p|(V_sin<<4);
        
        
        LATAbits.LATA0 = 0; //bring chip select low
        spi_io(p>>8); //write byte
        spi_io(p); //write second byte
        LATAbits.LATA0 = 1; //bring chip select high
        

        p=0;
        //triangle wave at DACB
        c = 0b0;
        V_tri = triangle[i]/3.3*256;
        //V_tri=2/3.3*256;
        p = (c<<15)|(0b111<<12)|(V_tri<<4);
        
        LATAbits.LATA0 = 0; //bring chip select low
        spi_io(p>>8); //write byte
        spi_io(p); //write second byte
        LATAbits.LATA0 = 1; //bring chip select high
        
        i++;
        if (i == NUMSAMPS) {
            i = 0;
        }

        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / NUMSAMPS) {;} // delay (1/1000 s)
    }
    
}