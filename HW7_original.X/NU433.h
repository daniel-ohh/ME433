#ifndef NU433__H__
#define NU433__H__

#include <xc.h>                     // processor SFR definitions
#include <sys/attribs.h>            // __ISR macro

void NU433setup(void);
void ReadUART1(char * string, int maxLength);
void WriteUART1(const char * string);

#endif // NU433__H__
