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


int main() {
    NU433setup();
    i2c_master_setup();
    unsigned char a;
    
    while (1) {
        
        //GP7 is an output(0))
        //GP0 is an input (1)
        
        setPin(0b0100000,0x00,0b00000001);
        
            a = readPin(0b0100000,0x09);
            if (a == 0) {
                _CP0_SET_COUNT(0);
                while (_CP0_GET_COUNT() < 48000000 / 40) {;} // delay (0.025 s)
                a = readPin(0b0100000,0x09);
                if (a==0) {
                    setPin(0b0100000,0x0A,0b10000000);
                    _CP0_SET_COUNT(0);
                    while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)   
                    setPin(0b0100000,0x0A,0b00000000);
                }
                
            }

                        //heartbeat
        LATAbits.LATA4 = 1;
        //setPin(0b0100000,0x0A,0b10000000);
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
        //setPin(0b0100000,0x0A,0b00000000);
        LATAbits.LATA4 = 0;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
    }
    
}