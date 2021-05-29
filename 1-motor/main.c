#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include "timer0.h"
#include "key.h"
#include "lcd.h"

// 占空比, 100 为最大
unsigned char level = 0;

sbit MOTOR = P1 ^ 0;

// 100us
void timer0_routine() interrupt 1
{
    static unsigned int t0_count = 0;
    TL0 = 0x9c;
    TH0 = 0xff;
    ++t0_count;
    if (t0_count >= 100)
    {
        t0_count = 0;
    }
    if (t0_count < level)
    {
        MOTOR = 1;
    }
    else
    {
        MOTOR = 0;
    }
}

void lcd_show_speed(unsigned char *str, int length)
{
    LCD_Init();
    LCD_WriteString(0, 0, str, length);
}

void main()
{
    unsigned char key_num = 0;
    unsigned char speed = 0;
    unsigned char buf[16];

    timer0_init();
    LCD_Init();

    while (1)
    {
        key_num = key_press();
        if (key_num == 1)
        {
            ++speed;
            speed %= 5;

            if (speed == 0) level = 0;
            if (speed == 1) level = 40;
            if (speed == 2) level = 55;
            if (speed == 3) level = 75;
            if (speed == 4) level = 100;

            sprintf(buf, "motor speed %bu", speed);
            lcd_show_speed(buf, 13);
        }

        // show(7, speed);
    }
}
