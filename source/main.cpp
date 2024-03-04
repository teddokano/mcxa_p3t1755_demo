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

/**
 * @file    mcxa_p3t1755_demo.cpp
 * @brief   Application entry point.
 */

extern "C" {
#include "config.h"

#include "fsl_debug_console.h"

#include "P3T1755.h"
#include "mcu.h"
#include "demo/led_control.h"
}

#include "i3c/i3c.h"
#include "demo/demo.h"

//#define	HIGHER_SCL_FREQ

#ifdef	HIGHER_SCL_FREQ
#define EXAMPLE_I3C_OD_FREQ		4000000UL
#define EXAMPLE_I3C_PP_FREQ		12500000UL
#else
#define EXAMPLE_I3C_OD_FREQ		1500000UL
#define EXAMPLE_I3C_PP_FREQ		4000000UL
#endif //HIGHER_SCL_FREQ

#define EXAMPLE_I2C_FREQ		400000UL

void		DAA_set_dynamic_ddress_from_static_ddress( uint8_t dynamic_address, uint8_t static_address );
float		temp_sensor_setting( uint8_t addr, uint8_t config );
void		temp_sensor_reg_dump( uint8_t addr );
float		read_temp( uint8_t targ, uint8_t reg );
void		write_temp( uint8_t targ, uint8_t reg, float v );
float		short2celsius( int16_t v );
int16_t		celsius2short( float v );
int16_t		swap_bytes( int16_t v );
void		wait( float delayTime_sec );

__attribute__((constructor)) void start_mcu() {
	init_mcu();
	PRINTF("\r\n********************\r\n");
}


I3C		i3c( EXAMPLE_I2C_FREQ, EXAMPLE_I3C_OD_FREQ, EXAMPLE_I3C_PP_FREQ );
P3T1755	p3t1755( i3c, P3T1755_ADDR_I3C );

extern	I3C	i3c;


/*
 * @brief   Application entry point.
 */
int main(void)
{
	init_demo();

	PRINTF("\r\nP3T1755 (Temperature sensor) I3C operation sample: getting temperature data and IBI\r\n");

	DAA_set_dynamic_ddress_from_static_ddress( P3T1755_ADDR_I3C, P3T1755_ADDR_I2C );

	float	ref_temp;
	ref_temp	= temp_sensor_setting( P3T1755_ADDR_I3C, P3T1755_CONFIG_VALUE );
	PRINTF( "  T_LOW / T_HIGH registers are set based on current temperature: %8.4f˚C\r\n", ref_temp );

	temp_sensor_reg_dump( P3T1755_ADDR_I3C );

	float	temp;
	uint8_t	ibi_addr;

	while ( true )
	{
		if ( (ibi_addr	= i3c.check_IBI()) )
			PRINTF("*** IBI : Got IBI from target_address: 7’h%02X (0x%02X)\r\n", ibi_addr, ibi_addr << 1 );

		temp	= p3t1755;
		PRINTF( "Temperature: %8.4f˚C\r\n", temp );
		demo( temp, &ref_temp, temp_sensor_setting );
		wait( 1 );
	}
}

void DAA_set_dynamic_ddress_from_static_ddress( uint8_t dynamic_address, uint8_t static_address )
{
	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 ); // Reset DAA
	i3c.ccc_set( CCC::DIRECT_SETDASA, static_address, dynamic_address << 1 ); // Set Dynamic Address from Static Address
}

float temp_sensor_setting( uint8_t addr, uint8_t config )
{
	float	temp, high, low;

	p3t1755.conf( config );

	temp	= p3t1755.temp();
	low		= temp + 1.0;
	high	= temp + 2.0;

	p3t1755.high( high );
	p3t1755.low(  low  );
	
	//	Enable IBI
	i3c.ccc_set( CCC::DIRECT_ENEC, addr, 0x01 );

	PRINTF( "  T_LOW / T_HIGH registers updated: %8.4f˚C / %8.4f˚C\r\n", low, high );

	return temp;
}

void temp_sensor_reg_dump( uint8_t addr )
{
	float		t, l, h;
	uint8_t		c;
	uint8_t		pid[ PID_LENGTH ];
	uint8_t		bcr, dcr;

	t	= p3t1755;
	c	= p3t1755.conf();
	h	= p3t1755.high();
	l	= p3t1755.low();
	
	i3c.ccc_get( CCC::DIRECT_GETPID, addr, pid, sizeof( pid ) );
	i3c.ccc_get( CCC::DIRECT_GETBCR, addr, &bcr, 1 );
	i3c.ccc_get( CCC::DIRECT_GETDCR, addr, &dcr, 1 );

	PRINTF( "\r\nRegister dump - I3C target address:7’h%02X (0x%02X)\r\n", P3T1755_ADDR_I3C, P3T1755_ADDR_I3C << 1 );
	PRINTF( "  - Temp   (0x0): 0x%04X (%8.4f˚C)\r\n", (uint16_t)P3T1755::celsius2short( t ), t );
	PRINTF( "  - Conf   (0x1): 0x  %02X\r\n", c );
	PRINTF( "  - T_LOW  (0x2): 0x%04X (%8.4f˚C)\r\n", (uint16_t)P3T1755::celsius2short( l ), l );
	PRINTF( "  - T_HIGH (0x3): 0x%04X (%8.4f˚C)\r\n", (uint16_t)P3T1755::celsius2short( h ), h );

	PRINTF( "  * PID    (CCC:Provisioned ID)                 : 0x" );
	for ( int i = 0; i < PID_LENGTH; i++ ) PRINTF( " %02X", pid[ i ] );	PRINTF( "\r\n" );
	PRINTF( "  * BCR    (CCC:Bus Characteristics Register)   : 0x%02X\r\n", bcr );
	PRINTF( "  * DCR    (CCC:Device Characteristics Register): 0x%02X (= %s)\r\n", dcr, (0x63 == dcr) ? "Temperature sensor" : "Unknown" );

	PRINTF( "\r\n" );
}
