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
#define DATA_PTS 300

char m_in[100];
char m_out[200];
float ax[DATA_PTS], ay[DATA_PTS], az[DATA_PTS], gx[DATA_PTS], gy[DATA_PTS], gz[DATA_PTS], temp[DATA_PTS];
char IMU_buf[IMU_ARRAY_LEN];

int main() {
    NU433setup();
    i2c_master_setup();
    init_mpu6050();
    int i;
    
//    while (1) {
//    WriteUART1("Enter your shit\r\n");
//    ReadUART1(m_in,100);
//    WriteUART1(m_in);
//    WriteUART1("\r\n");
//    }
//    //char who = whoami();
    while (1) {
        //WriteUART1("Waiting for Enter Key\r\n");
        ReadUART1(m_in,100);
        //WriteUART1("hello\r\n");
        for (i=0;i<DATA_PTS;i++) {
            burst_read_mpu6050(IMU_buf);
            ax[i] = conv_xXL(IMU_buf);
            ay[i] = conv_yXL(IMU_buf);
            az[i] = conv_zXL(IMU_buf);
            gx[i] = conv_xG(IMU_buf);
            gy[i] = conv_yG(IMU_buf);
            gz[i] = conv_zG(IMU_buf);
            temp[i] = conv_temp(IMU_buf);
            _CP0_SET_COUNT(0);
            while (_CP0_GET_COUNT()<24000000/2/100) {};
        }
        
        for (i=0;i<DATA_PTS;i++) {
            sprintf(m_out,"%d %f %f %f %f %f %f %f\r\n",DATA_PTS-i,ax[i],ay[i],az[i],gx[i],gy[i],gz[i],temp[i]);
            WriteUART1(m_out);
        }

//        _CP0_SET_COUNT(0);
//        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
//        //setPin(0b0100000,0x0A,0b00000000);
//        LATAbits.LATA4 = 0;
//        _CP0_SET_COUNT(0);
//        while (_CP0_GET_COUNT() < 48000000 / 4) {;} // delay (1/2 s)
//        LATAbits.LATA4 = 1;
    }
    
}