#include "utils.h"

int len(unsigned char *str)
{
    int res = 0, idx = 0;
    while (str[idx] != '\0')
    {
        ++res;
        ++idx;
    }
    return res;
}

unsigned char bcd2dec(unsigned char bcd)
{
    return bcd / 16 * 10 + bcd % 16;
}

unsigned char dec2bcd(unsigned char dec)
{
    return dec / 10 * 16 + dec % 10;
}

void delay1ms() //@12.000MHz
{
    unsigned char i, j;

    i = 2;
    j = 239;
    do
    {
        while (--j)
            ;
    } while (--i);
}

void delay(unsigned int ms)
{
    while (ms--)
    {
        delay1ms();
    }
}
