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
#include "mpu6050.h"


int main() {
    NU433setup();
    i2c_master_setup();
    init_mpu6050();
    
    char who;
    
    while (1) {
             
        //setPin(0b11010000
        who = whoami();

        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
        //setPin(0b0100000,0x0A,0b00000000);
        LATAbits.LATA4 = 0;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
    }
    
}