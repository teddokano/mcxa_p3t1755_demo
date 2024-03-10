/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_I2C_H
#define R01LIB_I2C_H


#define EXAMPLE_I2C_MASTER_BASE			LPI2C0
#define LPI2C_MASTER_CLOCK_FREQUENCY	CLOCK_GetLpi2cClkFreq()


#define EXAMPLE_I2C_MASTER				((LPI2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define LPI2C_BAUDRATE					100000U

class I2C
{
public:
	I2C( uint32_t frequency = LPI2C_BAUDRATE );
	~I2C();
	
	status_t	write( uint8_t address, const uint8_t *dp, int length );
	status_t	read( uint8_t address, uint8_t *dp, int length );

private:
};

#endif // R01LIB_I2C_H
