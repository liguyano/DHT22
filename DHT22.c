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
uint dht_read(uint* wet,uint* tmp,uchar* test)
{uint rTime=0;
    uchar i;
    Timer1Init();
    TL1 = 0x00;		//设置定时初值
    TH1 = 0x00;		//设置定时初值
    TR1 = 1;		//定时器1开始计时
    while (data && TF1!=0);
    TR1=0;
    if (TF1)
    {
        return 2222;
    }
    for (i=0;i<16;i++)
    {
        while (!data);
        Delay20us();
        if(data)
        {
            rTime|= 0x0001<<(16-i);
            while (data);
        }
    }
    if (rTime>3)
        *wet=rTime;
    rTime=0x0000;
    for (i=0;i<16;i++)
    {
        while (!data);
        Delay20us();
        if(data)
        {
            rTime|= 0x0001<<(16-i);
            while (data);
        }
    }
    *tmp=rTime;
    rTime=0x0000;
    for (i=0;i<8;i++)
    {
        while (!data);
        Delay20us();
        if(data)
        {
            rTime|= 0x0001<<(8-i);
            while (data);
        }
    }
    *test=rTime;
}
void Timer1Init(void)		//1毫秒@11.0592MHz
{
    AUXR |= 0x40;		//定时器时钟1T模式
    TMOD &= 0x0F;		//设置定时器模式

    TF1 = 0;		//清除TF1标志

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
