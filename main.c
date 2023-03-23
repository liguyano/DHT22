#include "SSS.h"
#include "MAtrix_key.h"
#include <STC15F2K60S2.H>
#include "DHT22.h"
#include <MATH.H>
static uint time=0;
static uint t1=0;
static uint t2=0;
unsigned char code SMG_duanma[18]=
{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
0xbf,0x7f};/*用于数码管段选*/
void SelectHC573(unsigned char channel)/*74HC573锁存器*/
{
    switch(channel)
    {
        /*
         * &0x1f 将前三位置0
         * | 0x80 将第一位置1
         * | 0xa0 1010 0000
         * */

        case 4:
            P2 = (P2 & 0x1f) | 0x80;
            break;
        case 5:
            P2 = (P2 & 0x1f) | 0xa0;
            break;
        case 6:
            P2 = (P2 & 0x1f)| 0xc0;//1100
            break;
        case 7:
            P2 = (P2 & 0x1f) | 0xe0;
            break;
    }
}

void DIAPlaySMG_Bit(unsigned char value, unsigned char pos)/*数码管显示*/
{
    P0 = 0xff;
    /*段选*/
    SelectHC573(6);
    P0 = 0x01 << pos;
    P2&=0x1f;
    /*位选*/
    SelectHC573(7);
    P0 = value;
    P2&=0x1f;
}

void DelaySMG(unsigned int t)/*数码管延时函数*/
{
    while(t--);
}
void showMoreNUm(unsigned char num,unsigned char start)
{
    unsigned char h,t=0;
    h=num/100;
    DIAPlaySMG_Bit(SMG_duanma[h],start+0);
    DelaySMG(50);
    num=num%100;
    t=num/10;
    DIAPlaySMG_Bit(SMG_duanma[t],start+1);DelaySMG(50);
    num%=10;
    DIAPlaySMG_Bit(SMG_duanma[num],start+2);DelaySMG(50);

}
void showIntNUm(unsigned int num)
{
    unsigned char i,s;
    for (i=1;i<6;i++)
    {
        s=num/ pow(10.0,5.0-i*1.0) ;
        num %= (unsigned int ) pow(10.0,5.0-i);
        DIAPlaySMG_Bit(SMG_duanma[s],i-1);
        Delay(10);
    }
}
void Timer0Init(void)		//1毫秒@11.0592MHz
{
    AUXR |= 0x80;		//定时器时钟1T模式
    ET0=1;
    EA=1;
    TMOD &= 0xF0;		//设置定时器模式
    TL0 = 0xCD;		//设置定时初值
    TH0 = 0xD4;		//设置定时初值
    TF0 = 0;		//清除TF0标志
    TR0 = 1;		//定时器0开始计时
}

void show3intNUm(unsigned int num,unsigned char start,unsigned char domma)
{
    unsigned char h,t=0;
    h=num/100;

    DIAPlaySMG_Bit(SMG_duanma[h],start+0);
    DelaySMG(50);
    num=num%100;
    t=num/10;
    if (domma)
        DIAPlaySMG_Bit(SMG_duanma[t]&0x7f,start+1);
    else
        DIAPlaySMG_Bit(SMG_duanma[t],start+1);DelaySMG(50);
    DelaySMG(50);
    num%=10;
    DIAPlaySMG_Bit(SMG_duanma[num],start+2);DelaySMG(50);

}
void main() {

    uchar test;
    Timer0Init();

    SelectHC573(5);
    P0&= 0xBF;
    P2&=0x1f;
    dht_start();
    dht_read(&t1,&t2,&test);
    while (1)
    {
        show3intNUm(t1,0,1);
        show3intNUm(t2,4, 1);
        Delay20us();
    }
}
void times() interrupt NUM1
{   time++;
    TL0 = 0xCD;		//设置定时初值
    TH0 = 0xD4;		//设置定时初值
    if (time>=3000)
    {
        dht_start();
        dht_read(&t1, &t2,0);
        time=0;
    }

}