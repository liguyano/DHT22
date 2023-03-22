//
// Created by kurum on 西暦2023年3月22日.
//
#include <INTRINS.H>
#include "DHT22.h"
void dht_start()
{
    data=1;
    data=0;
    Delay1000ms();
    data=1;
    Delay20us();
}
uint dht_read()
{
    while (data);
    return 0x55;
}
void Delay1000ms()		//@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    _nop_();
    _nop_();
    i = 11;
    j = 190;
    do
    {
        while (--j);
    } while (--i);
}
void Delay20us()		//@11.0592MHz
{
    unsigned char i;

    _nop_();
    _nop_();
    i = 80;
    while (--i);
}

void Delay80us()		//@11.0592MHz
{
    unsigned char i, j;

    _nop_();
    i = 1;
    j = 217;
    do
    {
        while (--j);
    } while (--i);
}
