/*
 * Copyright 2022 NXP
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This code based on a sample projects:
 *    "frdmmcxa153_i3c_master_read_sensor_p3t1755" from SDK_2.14.2_FRDM-MCXA153 and
 *    "lpcxpresso860max_i3c_master_read_sensor_icm42688p" from SDK_2.15.000_LPCXpresso860MAX
 */

extern "C" {
#include	"fsl_debug_console.h"
}

#include	"config.h"
#include	"P3T1755.h"
#include	"i3c.h"
#include	"demo.h"
#include	"mcu.h"
#include	"io.h"

void	DAA_set_dynamic_ddress_from_static_ddress( uint8_t dynamic_address, uint8_t static_address );

__attribute__((constructor)) void start_mcu() {
	init_mcu();
	PRINTF("\r\n***  MCU initialized properly  ***\r\n");
}

I3C		i3c;
P3T1755	p3t1755( i3c );

DigitalOut	red( D5 );
DigitalOut	green( D6 );
DigitalOut	blue( D3 );
DigitalOut	trigger( D3 );
//DigitalOut&	target	= blue;

extern	I3C	i3c;

int main(void)
{
	init_demo();

	PRINTF("\r\nP3T1755 (Temperature sensor) I3C operation sample: getting temperature data and IBI\r\n");

	DAA_set_dynamic_ddress_from_static_ddress( P3T1755_ADDR_I3C, P3T1755_ADDR_I2C );
	p3t1755.address_overwrite( P3T1755_ADDR_I3C );
	
	float ref_temp	= p3t1755.temp();
	float low		= ref_temp + 1.0;
	float high		= ref_temp + 2.0;

	p3t1755.high( high );
	p3t1755.low(  low  );

	PRINTF( "  T_LOW / T_HIGH registers updated: %8.4f˚C / %8.4f˚C\r\n", low, high );
	PRINTF( "      based on current temperature: %8.4f˚C\r\n", ref_temp );

	p3t1755.conf( p3t1755.conf() | 0x02 );		//	ALART pin configured to INT mode
	p3t1755.ccc_set( CCC::DIRECT_ENEC, 0x01 );	// Enable IBI

	p3t1755.info();

	float	temp;
	uint8_t	ibi_addr;

	while ( true )
	{
		if ( (ibi_addr	= i3c.check_IBI()) )
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\r\n", ibi_addr, ibi_addr << 1 );

		temp	= p3t1755;
		PRINTF( "Temperature: %8.4f˚C\r\n", temp );

		demo( temp, &ref_temp );
		wait( 1 );
	}
}

void DAA_set_dynamic_ddress_from_static_ddress( uint8_t dynamic_address, uint8_t static_address )
{
	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	i3c.ccc_set( CCC::DIRECT_SETDASA, static_address, dynamic_address << 1 ); // Set Dynamic Address from Static Address
}
