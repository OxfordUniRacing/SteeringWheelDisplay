/*
@file    FT8_config.c
@brief   Contains hardware abstraction functions for using the FT8xx
@version 3.0
@date    2017-04-02
@author  Rudolph Riedel

This file needs to be renamed to FT8_config.cpp for use with Arduino. 

@section History

2.2
- extracted from FT8_commands.c
- added FT8_pdn_set() and FT8_pdn_clear()
- replaced spi_flash_write() with fetch_flash_byte()

2.3
- added set of functions for Arduino

2.4
- switched from custom AVR8 to standard __AVR__ symbol to automatically generate plattform specific code

2.5
- added support for RH850
- switched to standard-C compliant comment-style

3.0
- renamed from FT800_config.c to FT8_config.c
- changed FT_ prefixes to FT8_
- changed ft800_ prefixes to FT8_

*/

#include "FT8_config.h"

void FT8_cs_set(void)
{
	SPI.setDataMode(SPI_MODE0);
	digitalWrite(FT8_CS, LOW);
}


void FT8_cs_clear(void)
{
	digitalWrite(FT8_CS, HIGH);
}

void FT8_pdn_set(void)
{
	digitalWrite(FT8_PDN, LOW);	/* Power-Down low */
}


void FT8_pdn_clear(void)
{
	digitalWrite(FT8_PDN, HIGH);	/* Power-Down high */
}

void spi_transmit(uint8_t data)
{
	SPI.transfer(data);
}


uint8_t spi_receive(uint8_t data)
{
	return SPI.transfer(data);
}

uint8_t fetch_flash_byte(const uint8_t *data)
{
	return(pgm_read_byte_near(data));
}

