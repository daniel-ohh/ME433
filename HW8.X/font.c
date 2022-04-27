#include "font.h"
#include "ssd1306.h"
#include <string.h>
void drawChar(unsigned char x_init, unsigned char y_init, char c) {
    int i = c-32;
    int x, y;
    int col;
    for (col=0;col<5;col++) {
        x = x_init + col;
        char key = ASCII[i][col];
        int bit = 0;
        while (bit<8) {
            y = y_init+bit;
            if (key & 0x01) {
                ssd1306_drawPixel(x,y,1);// bit is 1, turn on
            }
            else {;}   
            key = key >> 1;
            bit++;
        }
        
    }
    ssd1306_update();
}

void drawStr(unsigned char x, unsigned char y, char * string) {
    int len = strlen(string);
    int i;
    for (i=0;i<len;i++) {
        
        drawChar(x,y,string[i]);
        x = x + 6;
                
    }
    ssd1306_update();
}