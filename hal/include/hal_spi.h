#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "io430.h"

void hal_spi_init(void); // initialize SPI
unsigned char hal_spi_transfer(unsigned char txbyte); // transfer a single byte between master and slave (does not cover toggling the CS line, this needs to be done by the caller)

#endif