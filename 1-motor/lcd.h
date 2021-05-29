#ifndef __LCD_H__
#define __LCD_H__

// led numeric
void show(unsigned int order, unsigned int number);

sbit LCD_RW = P2 ^ 5;
sbit LCD_RS = P2 ^ 6;
sbit LCD_E = P2 ^ 7;

#define LCD_DataPort P0

void LCD_Init();
void LCD_WriteCommand(unsigned char cmd);
void LCD_WriteData(unsigned char l_data);
void LCD_WriteString(unsigned char row, unsigned char col, unsigned char *str, int length);

void lcd_print(unsigned char *str, int length);

#endif
