#ifndef __UTILS_H__
#define __UTILS_H__

int len(unsigned char *str);

unsigned char bcd2dec(unsigned char bcd);
unsigned char dec2bcd(unsigned char dec);

void delay(unsigned int ms);

#endif
