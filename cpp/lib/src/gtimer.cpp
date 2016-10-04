#include "gtimer.h"

PtrTimer Gtimer::iniTimer [5] = {&Gtimer::clockTimer3, &Gtimer::clockTimer14, &Gtimer::clockTimer15, &Gtimer::clockTimer16, &Gtimer::clockTimer17};

TIM_TypeDef * Gtimer::timerBase [5] = {TIM3, TIM14, TIM15, TIM16, TIM17};

Gtimer::Gtimer (nTimer n, uint16_t divider)
{
	n_ = n;
	setPsc (divider);
}

Gtimer::Gtimer (nTimer n)
{
	n_ = n;
	(this->*(Gtimer::iniTimer[n_]))();
}

void Gtimer::setCnt (uint16_t val)
{
	timerBase [n_]->CNT = val;
}

void Gtimer::setPsc (uint16_t p)
{
	timerBase [n_]->PSC = p-1;
}

void Gtimer::setArr (uint16_t a)
{
	timerBase [n_]->ARR = a;
}

void Gtimer::setChannelValue (uint16_t val)
{
	timerBase [n_]->CCR1 |= val << (ch_*16);
}

uint16_t Gtimer::getCnt ()
{
	return timerBase [n_]->CNT;
}

void Gtimer::Start ()
{
	timerBase [n_]->CR1 |= TIM_CR1_CEN;
}

void Gtimer::Stop ()
{
	timerBase [n_]->CR1 &= ~TIM_CR1_CEN;
}

void Gtimer::ClearFlag()
{
	
}

void Gtimer::clockTimer3 ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
}

void Gtimer::clockTimer14 ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
}

void Gtimer::clockTimer15 ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
}
	
void Gtimer::clockTimer16 ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
}

void Gtimer::clockTimer17 ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
}
