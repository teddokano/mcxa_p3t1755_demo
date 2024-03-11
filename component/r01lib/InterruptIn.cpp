/*
 * Copyright 2017 NXP
 * Copyright 2024 Tedd OKANO
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */

extern "C" {
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"

}

#include	"io.h"
#include	"InterruptIn.h"

void irq_handler( int num );


void GPIO0_IRQHandler( void )
{
	irq_handler( 0 );
}

void GPIO1_IRQHandler( void )
{
	irq_handler( 1 );
}

void GPIO2_IRQHandler( void )
{
	irq_handler( 2 );

}

void GPIO3_IRQHandler( void )
{
	irq_handler( 3 );
}

void GPIO4_IRQHandler( void )
{
	irq_handler( 4 );
}

void irq_handler( int num )
{
	PRINTF( "######################### %d\r\n", num );

}





InterruptIn::InterruptIn( uint8_t pin_num )
	: DigitalIn( pin_num )
{
}

InterruptIn::~InterruptIn() {}

void InterruptIn::fall( utick_callback_t callback )
{
	/* Init input switch GPIO. */
	#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
		GPIO_SetPinInterruptConfig( gpio_n, gpio_pin, kGPIO_InterruptFallingEdge );
	#else
		PORT_SetPinInterruptConfig( gpio_n, gpio_pin, kGPIO_InterruptFallingEdge );
	#endif

#if 1
	EnableIRQ( GPIO0_IRQn );
	EnableIRQ( GPIO1_IRQn );
	EnableIRQ( GPIO2_IRQn );
	EnableIRQ( GPIO3_IRQn );
//	EnableIRQ( GPIO4_IRQn );
#endif
}
