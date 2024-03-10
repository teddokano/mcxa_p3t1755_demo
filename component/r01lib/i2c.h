/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_I2C_H
#define R01LIB_I2C_H

#define LPI2C_BAUDRATE					100000U

#define	STOP			true
#define	NO_STOP			false



class I2C
{
public:
	I2C( uint32_t frequency = LPI2C_BAUDRATE );
	~I2C();
	
	status_t	write( uint8_t address, const uint8_t *dp, int length, bool stop = STOP );
	status_t	read( uint8_t address, uint8_t *dp, int length, bool stop = STOP );

private:
};

#endif // R01LIB_I2C_H
