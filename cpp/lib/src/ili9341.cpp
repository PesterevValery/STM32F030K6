#include "ili9341.h"




Ili9341::Ili9341(Spi &d, Gpio::Port po, uint8_t p, Gpio::Port rstpo, uint8_t rstpi)
:dc (po, p, Gpio::Omode::PushPull), rst (rstpo, rstpi, Gpio::Omode::PushPull), cs (Gpio::Port::A, 4, Gpio::Omode::PushPull)
{
	driver = &d;
	driver->setCpol(Spi::cpol::neg);
	driver->setCpha(Spi::cpha::first);
	driver->setBaudrate(Spi::division::div8);
	driver->setFsize(Spi::fsize::bit_8);
	cs.set ();
	SPI1->CR1 |= SPI_CR1_BIDIMODE|SPI_CR1_BIDIOE ;
	
	driver->start();
	init ();
	driver->setBaudrate(Spi::division::div2);
	
}

void Ili9341::setDma (Dma &d)
{
	dma = &d;
 dma->setDirection (Dma::direction::mem2periph);
	dma->setSize(Dma::size::bit16, Dma::size::bit16);
	dma->setPtrPeriph((uint32_t)&driver->getSpiPtr()->DR);
 dma->setIncPer (false);
 dma->setInterrupt (true);
 driver->getSpiPtr()->CR2 |= SPI_CR2_TXDMAEN;
}

void Ili9341::fillScreen (const uint16_t color)
{

	/*command (ili9341Commands::memoryWrite);
	driver->setFrameSize(Spi::Size::bit16);
	dma->setIncSource(false);
	dataDma (&color, 76800);
	driver->setFrameSize(Spi::Size::bit8);*/

	/*unsigned int n, i, j;
		i = color >> 8;
		j = color & 0xFF;*/

		setColoumn(100, 150);
		setPage (100, 150);


		command(ili9341Commands::memoryWrite);
		//driver->setFsize(Spi::fsize::bit_16);
		dc.set();
		
/*
  dma->setIncMem (false);
	dma->setPtrMem ((uint32_t)&color);
  dma->setLength (0xFFFF);
		
  dma->start ();*/
	for (uint32_t n = 0; n < 2500; n++) 
	{
		cs.clear ();
			while (!driver->flagTxe());
			driver->putData(color>>8);
			while (!driver->flagTxe());
			driver->putData(color);
			while (driver->flagBsy());
		cs.set ();	
	}
		
		
		//driver->setFsize(Spi::fsize::bit_8);
}

void Ili9341::setCursor (uint16_t x , uint16_t y)
{

}

void Ili9341::setCursor (uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2)
{
	command(ili9341Commands::coloumnAddressSet);
	data(x1 >> 8);
	data(x1 & 0xFF);
	data(x2 >> 8);
	data(x2 & 0xFF);

	command(ili9341Commands::pageAddressSet);
	data(y1 >> 8);
	data(y1 & 0xFF);
	data(y2 >> 8);
	data(y2 & 0xFF);

}

void Ili9341::chipEnable ()
{
  cs.clear ();	
}

void Ili9341::chipDisable ()
{
 cs.set ();	
}

void Ili9341::data (uint8_t dta)
{
	dc.set();
	cs.clear ();	
	driver->putData(dta);
	while (driver->flagBsy());
	cs.set ();
}


void Ili9341::data16 (uint16_t dta)
{
	dc.set();
	cs.clear ();	
	driver->putData(dta >> 8);
	while (!driver->flagTxe());
	driver->putData(dta);
	while (driver->flagBsy());
	cs.set ();
}

void Ili9341::dataDma (uint16_t * buf, uint32_t n)
{
	/*dma->setSource((uint32_t)buf);
	dma->setLength(n);
	driver->enableDma(Spi::dma::transmit);
	while (!dma->flagDone());
	dma->clearFlags();
	driver->disableDma(Spi::dma::transmit);*/
}


void Ili9341::command (uint8_t com)
{
	dc.clear();
	cs.clear ();
	driver->putData(com);
	while (driver->flagBsy());
	cs.set ();
}

void Ili9341::init ()
{
	rst.set();
	delay_ms(5);
	rst.clear();
	delay_ms(20);
	rst.set();
	delay_ms(150);

	command (ili9341Commands::softwareReset);
	delay_ms(1000);
	command (ili9341Commands::powerControl1);
	data(0x25);

	command (ili9341Commands::powerControl2);
	data(0x11);

	command (ili9341Commands::vcomControl1);
	data(0x2B);
	data(0x2B);

	command (ili9341Commands::vcomControl2);
	data(0x86);

	//orient
	command (ili9341Commands::memryAccessControl);
	data(0x28);

	command (ili9341Commands::pixelFormatSet);
	data(0x55);

	command (ili9341Commands::frameControl);
	data(0x00);
	data(0x18);

	command (ili9341Commands::pixelFormatSet);
	data(0x55);

	command (ili9341Commands::displayFunctionControl);
	data(0x0A);
	data(0x82);
	data(0x27);

	command (ili9341Commands::sleepOut);
	delay_ms(120);

	command (ili9341Commands::displayOn);
}

void Ili9341::setPage (uint16_t y1, uint16_t y2)
{
	command (ili9341Commands::pageAddressSet);
	data (y1>>8);
	data (y1&0xFF);
	data (y2>>8);
	data (y2&0xFF);
}

void Ili9341::setColoumn (uint16_t x1, uint16_t x2)
{
	command (ili9341Commands::coloumnAddressSet);
	data (x1>>8);
	data (x1&0xFF);
	data (x2>>8);
	data (x2&0xFF);
}

void Ili9341::setPosition (uint16_t x, uint16_t y)
{
	setColoumn (x, x);
	setPage (y, y);
	command (ili9341Commands::memoryWrite);
}

void Ili9341::pixel (const uint16_t color)
{
	/*command (ili9341Commands::memoryWrite);
	driver->setFrameSize(Spi::Size::bit16);
	data16 (color);
	driver->setFrameSize(Spi::Size::bit8);*/
}

