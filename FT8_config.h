/*
@file    FT8_config.h
@brief   configuration information for some TFTs and some pre-defined colors
@version 3.1
@date    2017-04-25
@author  Rudolph Riedel

@section History

2.2
- added prototypes for hardware abstraction funtions
- added hardware-selection defines, first implemented for AVR8
- added FT8_VM800B50A TFT setup as copy of FT8_VM800B43A since FTDI uses the same setup for both

2.3
- moved pin definitions for FT8_CS and FR_PDN to here from FT8_config.c
- added a set of definitions for Arduino

2.4
- switched from custom AVR8 to standard __AVR__ symbol to automatically generate plattform specific code
- removed the definition of the ARDUINO symbol at it already is defined by the Arduino enviroment

2.5
- added support for RH850
- switched to standard-C compliant comment-style
- added FT8_HAS_CRYSTAL to make FT8_init() automatically use the correct option

3.0
- renamed from FT800_config.h to FT8_config.h
- changed FT_ prefixes to FT8_
- changed ft800_ prefixes to FT8_

3.1

- added "#if defined (__ESP8266__)" for the Arduino side, now empty

*/

#ifndef FT8_CONFIG_H_
#define FT8_CONFIG_H_

/* switch over to FT81x */
#define FT8_81X_ENABLE

/* some pre-definded colors */
#define RED		0xff0000UL
#define ORANGE	0xffa500UL
#define GREEN	0x00ff00UL
#define BLUE	0x0000ffUL
#define YELLOW	0xffff00UL
#define PURPLE	0x800080UL
#define WHITE	0xffffffUL
#define BLACK	0x000000UL




#include <stdio.h>
#include <SPI.h>

#define FT8_CS 		10
#define FT8_PDN		2

#define DELAY_MS(ms) delay(ms)


void FT8_pdn_set(void);
void FT8_pdn_clear(void);
void FT8_cs_set(void);
void FT8_cs_clear(void);
void spi_transmit(uint8_t data);
uint8_t spi_receive(uint8_t data);
uint8_t fetch_flash_byte(const uint8_t *data);

// TFT Display Settings
#define FT8_VSYNC0    (0L)  /* Tvf Vertical Front Porch */
#define FT8_VSYNC1    (10L) /* Tvf + Tvp Vertical Front Porch plus Vsync Pulse width */
#define FT8_VOFFSET   (23L) /* Tvf + Tvp + Tvb Number of non-visible lines (in lines) */
#define FT8_VCYCLE    (525L)  /* Tv Total number of lines (visible and non-visible) (in lines) */
#define FT8_VSIZE     (272L)  /* Tvd Number of visible lines (in lines) - display height */
#define FT8_HSYNC0    (0L)  /* Thf Horizontal Front Porch */
#define FT8_HSYNC1    (10L) /* Thf + Thp Horizontal Front Porch plus Hsync Pulse width */
#define FT8_HOFFSET   (46L) /* Thf + Thp + Thb Length of non-visible part of line (in PCLK cycles) */
#define FT8_HCYCLE    (1056L) /* Th Total length of line (visible and non-visible) (in PCLKs) */
#define FT8_HSIZE     (480L)  /* Thd Length of visible part of line (in PCLKs) - display width */
#define FT8_PCLKPOL   (1L)  /* PCLK polarity (0 = rising edge, 1 = falling edge) */
#define FT8_SWIZZLE   (0L)  /* Defines the arrangement of the RGB pins of the FT800 */
#define FT8_PCLK      (2L)  /* 60MHz / REG_PCLK = PCLK frequency 30 MHz */
#define FT8_TOUCH_RZTHRESH (1800L)  /* touch-sensitivity */
#define FT8_HAS_CRYSTAL 0

#endif /* FT8_CONFIG_H */
