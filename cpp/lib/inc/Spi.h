#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"

#ifndef SPI_H
#define SPI_H

typedef unsigned int* reg;


class spi
{
//variables
public:
  enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
  enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {falling, rising};
  enum pin_def {CS = 4 , SCK , MISO , MOSI};
private:
  Gpio pin;
  
//function
public:
  spi(Division div, Cpol cpl = neg, Cpha cph = falling, Role r = master);
  void Set_CS ();
  void Clear_CS ();
  uint8_t transfer (uint8_t data);
private:
};

#endif
