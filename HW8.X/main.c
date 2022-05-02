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
#include "ssd1306.h"
#include "font.h"

int main() {
    NU433setup();
    i2c_master_setup();
    init_mpu6050();
    ssd1306_setup();
    float i, count, time;
    char array[50];
    while (1) {
        _CP0_SET_COUNT(0);
        ssd1306_clear();
        ssd1306_update();
        count = _CP0_GET_COUNT();
        time = count/24000000;
        i = 1/time;
        sprintf(array,"FPS: %0.2f", i);
        drawStr(62,24,array);
        delay(0.15);

//       LATAbits.LATA4 = 1;
//       _CP0_SET_COUNT(0);
//       while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
//       //drawChar(0,0,'#');
//       drawStr(0,0,"abcde");
//       LATAbits.LATA4 = 0;
//       _CP0_SET_COUNT(0);
//       while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
//       ssd1306_clear();
//       ssd1306_update();
    }
    
}