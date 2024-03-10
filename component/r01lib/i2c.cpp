/*
 * Copyright 2017 NXP
 * Copyright 2024 Tedd OKANO
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */

extern "C" {
#include <stdio.h>
#include <string.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
}

#include	"i2c.h"

I2C::I2C( uint32_t frequency )
{
	lpi2c_master_config_t	masterConfig;

	LPI2C_MasterGetDefaultConfig( &masterConfig );
	masterConfig.baudRate_Hz	= frequency;
	LPI2C_MasterInit( EXAMPLE_I2C_MASTER, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY );
}

I2C::~I2C() {}

status_t I2C::write( uint8_t address, const uint8_t *dp, int length )
{
	status_t	r = kStatus_Fail;
	size_t		txCount	= 0xFFU;

	if ( (r = LPI2C_MasterStart( EXAMPLE_I2C_MASTER, address, kLPI2C_Write )) )
		return r;

	do {
		LPI2C_MasterGetFifoCounts( EXAMPLE_I2C_MASTER, NULL, &txCount );
	} while ( txCount );

	if ( LPI2C_MasterGetStatusFlags( EXAMPLE_I2C_MASTER ) & kLPI2C_MasterNackDetectFlag )
		return kStatus_LPI2C_Nak;

	if ( (r	= LPI2C_MasterSend( EXAMPLE_I2C_MASTER, (uint8_t *)dp, length )) )
	{
		if ( r == kStatus_LPI2C_Nak )
			LPI2C_MasterStop( EXAMPLE_I2C_MASTER );

		return r;
	}

	return LPI2C_MasterStop( EXAMPLE_I2C_MASTER );
}


status_t I2C::read( uint8_t address, uint8_t *dp, int length )
{
	status_t	r = kStatus_Fail;
	size_t		txCount	= 0xFFU;

	if ( (r = LPI2C_MasterStart( EXAMPLE_I2C_MASTER, address, kLPI2C_Read )) )
		return r;

	do {
		LPI2C_MasterGetFifoCounts( EXAMPLE_I2C_MASTER, NULL, &txCount );
	} while ( txCount );

	if ( LPI2C_MasterGetStatusFlags( EXAMPLE_I2C_MASTER ) & kLPI2C_MasterNackDetectFlag )
		return kStatus_LPI2C_Nak;

	if ( (r	= LPI2C_MasterReceive( EXAMPLE_I2C_MASTER, dp, length )) )
		return r;

	return LPI2C_MasterStop( EXAMPLE_I2C_MASTER );
}
