#ifndef __DS1302_H__
#define __DS1302_H__

#include <REGX52.h>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

typedef struct {
    unsigned char second;
    unsigned char minites;
    unsigned char hour;
    unsigned char date;
    unsigned char month;
    unsigned char week;
    unsigned char year;
} ds_time;

#define DS1302_CMD_SEC    0x80
#define DS1302_CMD_MIN    0x82
#define DS1302_CMD_HOUR   0x84
#define DS1302_CMD_DATE   0x86
#define DS1302_CMD_MONTH  0x88
#define DS1302_CMD_DAY    0x8a
#define DS1302_CMD_YEAR   0x8c
#define DS1302_CMD_WRITE_PT 0x8e

void DS1302_Init();
void DS1302_WriteByte(unsigned char command, unsigned char dat);
unsigned char DS1302_ReadByte(unsigned char command);

void set_time(ds_time t);
ds_time current_time();

#endif
