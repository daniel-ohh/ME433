/* 
 * File:   main.c
 * Author: danieloh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro
#include "NU433.h"
#include "i2c_master_noint.h"
#include "ws2812b.h"

int main() {
    NU433setup();
    LATAbits.LATA4 = 1;
    i2c_master_setup();
    ws2812b_setup();
    int i;
    wsColor c[4];
//    c = HSBtoRGB(0,0.3,0.4);
    float colorval[4];
    colorval[0] = 0;
    colorval[1] = 45;
    colorval[2] = 90;
    colorval[3] = 135;
    
    while (1) {
        c[0] = HSBtoRGB(colorval[0],0.6,0.01);
        c[1] = HSBtoRGB(colorval[1],0.6,0.01);
        c[2] = HSBtoRGB(colorval[2],0.6,0.01);
        c[3] = HSBtoRGB(colorval[3],0.6,0.01);
        ws2812b_setColor(c, 4);
        
        for (i=0;i<4;i++) {
            colorval[i] = colorval[i] +.1;
            if (colorval[i] > 360) {
                colorval[i] = 0;
            }
        }
        
        }
    }