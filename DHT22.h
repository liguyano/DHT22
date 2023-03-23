//
// Created by kurum on 西暦2023年3月22日.
//

#ifndef PRO_DHT22_DHT22_H
#define PRO_DHT22_DHT22_H
#include <SSS.h>
#include <STC15F2K60S2.H>
#define data P30
void Delay1000ms();
void Delay20us();
void Delay80us();
void dht_start();
uint dht_read(uint* wet,uint* tmp,uchar* test);


#endif //PRO_DHT22_DHT22_H
