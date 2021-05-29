#include <REGX52.H>
#include "key.h"
#include "utils.h"

#define K1 P3_1
#define K2 P3_0
#define K3 P3_2
#define K4 P3_3

unsigned char key_press()
{
    unsigned char key_number = 0;

    if (K1 == 0)
    {
        delay(20);
        while (K1 == 0);
        delay(20);
        key_number = 1;
    }
    if (K2 == 0)
    {
        delay(20);
        while (K2 == 0);
        delay(20);
        key_number = 2;
    }
    if (K3 == 0)
    {
        delay(20);
        while (K3 == 0);
        delay(20);
        key_number = 3;
    }
    if (K4 == 0)
    {
        delay(20);
        while (K4 == 0);
        delay(20);
        key_number = 4;
    }

    return key_number;
}
