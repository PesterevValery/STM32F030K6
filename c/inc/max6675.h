#include "stm32f0xx.h"                  // Device header
#include "delay.h"

//Soft Spi
//#define SOFTSPI

//Pins for Soft Spi
#define sclk 5
#define miso 6
#define cs 4

#ifndef MAX6675_H
#define MAX6675_H


void max6675_init (void);

uint8_t readCelsius(void);

uint8_t spiread(void);



#endif