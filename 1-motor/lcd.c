#include <REGX52.h>
#include "utils.h"
#include "lcd.h"

unsigned char led_number_table[10] = {
    0x3f, // 0
    0x06, // 1
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
};

void select_led(unsigned int n)
{
    P2_2 = 0x01 & n;
    P2_3 = 0x02 & n;
    P2_4 = 0x04 & n;
}

void show_number(unsigned int n)
{
    unsigned char reg_value = led_number_table[n];
    P0 = reg_value;
    delay(1);
    P0 = 0x00;
}

void show(unsigned int order, unsigned int number)
{
    select_led(order);
    show_number(number);
}

void LCD_Init()
{
    LCD_WriteCommand(0x38);
    LCD_WriteCommand(0x0c);
    LCD_WriteCommand(0x06);
    LCD_WriteCommand(0x01);
}

void LCD_WriteCommand(unsigned char cmd)
{
    LCD_RS = 0;
    LCD_RW = 0;

    LCD_DataPort = cmd;
    LCD_E = 1;
    delay(1);
    LCD_E = 0;
    delay(1);
}

void LCD_WriteData(unsigned char l_data)
{
    LCD_RS = 1;
    LCD_RW = 0;

    if (l_data == ' ')
        l_data = 0x20;
    LCD_DataPort = l_data;
    LCD_E = 1;
    delay(1);
    LCD_E = 0;
    delay(1);
}

void LCD_SetCursor(unsigned char row, unsigned char col)
{
    if (row == 0)
    {
        LCD_WriteCommand(0x80 | col);
    }
    else
    {
        LCD_WriteCommand(0x80 | (0x40 + col));
    }
}

void LCD_WriteString(unsigned char row, unsigned char col, unsigned char *str, int length)
{
    int offset = 0;
    LCD_SetCursor(row, col);
    for (; offset < length; offset++)
    {
        LCD_WriteData(str[offset]);
    }
}

void lcd_print(unsigned char *str, int length)
{
    int offset = 0;
    int lcd_char_len = 0;
    int lcd_count = 0;
    int remain_count = 0;
    int idx = 0;
    int tmp = 0;
    for (; offset < length;)
    {
        tmp = length - lcd_count * 64;
        remain_count = tmp / 16;
        if (tmp % 16 > 0)
        {
            ++remain_count;
        }

        LCD_Init();
        for (idx = 0; idx < remain_count && idx < 4; idx++)
        {
            lcd_char_len = tmp - idx * 16;
            if (lcd_char_len > 16)
            {
                lcd_char_len = 16;
            }
            if (idx >= 2)
            {
                LCD_WriteString(idx % 2, 16, &str[offset + idx * 16], lcd_char_len);
            }
            else
            {
                LCD_WriteString(idx % 2, 0, &str[offset + idx * 16], lcd_char_len);
            }
        }

        ++lcd_count;
        offset = lcd_count * 64 + offset;

        delay(2000);
        if (idx < 2)
        {
            continue;
        }
        for (tmp = 0; tmp < 16; tmp++)
        {
            LCD_WriteCommand(0x18);
        }
        delay(2000);
    }
}