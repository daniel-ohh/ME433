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
    i2c_master_setup();
    ws2812b_setup();
//    wsColor c[4];
    wsColor c;
    c = HSBtoRGB(180,0.3,0.4);
//    c[0] = HSBtoRGB(60,0.3,0.4);
//    c[1] = HSBtoRGB(30,0.3,0.4);
//    c[2] = HSBtoRGB(60,0.3,0.4);
//    c[3] = HSBtoRGB(90,0.3,0.4);
    
    while (1) {
        
//        for (i=0;i<4;i++) {
//            c[i] = HSBtoRGB(j,0.7,0.4);
//            j = j+30; 
//            if (j >= 360) {
//                j = 0;
//            }
//        }
        LATAbits.LATA4 = 1;
        ws2812b_setColor(&c, 4);
//        j = j+30;
//        if (j>=360) {
//            j = 0;
//        }
        
        }
    }