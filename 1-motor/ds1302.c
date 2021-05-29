#include "ds1302.h"
#include "utils.h"

void sclk_falling_pulse()
{
    DS1302_SCLK = 1;
    DS1302_SCLK = 0;
}

void sclk_rising_pulse()
{
    DS1302_SCLK = 0;
    DS1302_SCLK = 1;
}

void DS1302_Init()
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_WriteByte(unsigned char command, unsigned char dat)
{
    unsigned char offset;
    DS1302_CE = 1;
    for (offset = 0; offset < 8; offset++)
    {
        DS1302_IO = (command >> offset) & 0x01;
        sclk_falling_pulse();
    }

    for (offset = 0; offset < 8; offset++)
    {
        DS1302_IO = (dat >> offset) & 0x01;
        sclk_falling_pulse();
    }

    DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char command)
{
    unsigned char offset, dat = 0x00, tmp;
    command |= 0x01;
    DS1302_CE = 1;
    for (offset = 0; offset < 8; offset++)
    {
        DS1302_IO = (command >> offset) & 0x01;
        sclk_rising_pulse();
    }

    for (offset = 0; offset < 8; offset++)
    {
        sclk_falling_pulse();
        tmp = DS1302_IO;
        dat = (dat >> 1) | (tmp << 7);
    }
    DS1302_CE = 0;

    return dat;
}

void set_time(ds_time t)
{
    DS1302_WriteByte(DS1302_CMD_WRITE_PT, 0x00);
    DS1302_WriteByte(DS1302_CMD_SEC, dec2bcd(t.second));
    DS1302_WriteByte(DS1302_CMD_MIN, dec2bcd(t.minites));
    DS1302_WriteByte(DS1302_CMD_HOUR, dec2bcd(t.hour));
    DS1302_WriteByte(DS1302_CMD_DATE, dec2bcd(t.date));
    DS1302_WriteByte(DS1302_CMD_MONTH, dec2bcd(t.month));
    DS1302_WriteByte(DS1302_CMD_DAY, dec2bcd(t.week));
    DS1302_WriteByte(DS1302_CMD_YEAR, dec2bcd(t.year));
}

ds_time current_time()
{
    ds_time cur;
    cur.second = bcd2dec(DS1302_ReadByte(DS1302_CMD_SEC));
    cur.minites = bcd2dec(DS1302_ReadByte(DS1302_CMD_MIN));
    cur.hour = bcd2dec(DS1302_ReadByte(DS1302_CMD_HOUR));
    cur.date = bcd2dec(DS1302_ReadByte(DS1302_CMD_DATE));
    cur.month = bcd2dec(DS1302_ReadByte(DS1302_CMD_MONTH));
    cur.week = bcd2dec(DS1302_ReadByte(DS1302_CMD_DAY));
    cur.year = bcd2dec(DS1302_ReadByte(DS1302_CMD_YEAR));

    return cur;
}