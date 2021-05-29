#include <REGX52.h>
#include <STDDEF.H>
#include "timer0.h"

static void *_fp_handlers[8] = {NULL};
static char _idx = -1;

// 100us @12.000MHz
void timer0_init()
{
    int i = 0;
    TMOD &= 0xf0;
    TMOD |= 0x01;
    TL0 = 0x9c;
    TH0 = 0xff;
    ET0 = 1;
    TF0 = 0;
    TR0 = 1;        // 定时器 0 开始计时
    EA = 1;
    PT0 = 0;

    _idx = -1;
    for (i = 0; i < 8; i++)
    {
        _fp_handlers[i] = NULL;
    }
}

void do_routine()
{
    int idx = 0;
    for (idx = 0; idx < 8; idx++)
    {
        void (*_fp)() = _fp_handlers[idx];
        if (_fp == NULL)
        {
            break;
        }
        _fp();
    }
}

void register_rontine(void (*fp)())
{
    ++_idx;
    if (_idx >= 8)
    {
        _idx = 0;
    }
    _fp_handlers[_idx] = fp;
}
