/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

extern "C" {
#include	"fsl_utick.h"

#include	"demo/pwm.h"
}

#include	"config.h"
#include	"mcu.h"
#include	"io.h"
#include	"led_control.h"

extern DigitalOut	red;
extern DigitalOut	green;
extern DigitalOut	blue;
extern DigitalOut	trigger;
extern DigitalOut&	target	= blue;

void init_pins( void );

static void led_control_callback( void )
{
	static int	count	= 0;
	int			c200;
	
	c200	= (BLUE == target) ? count % 200 : 100;
	pwm_update( (100 < c200) ? 200 - c200 : c200 );

	led_pin_control( count );
	
	count++;
}


//void init_led( void )
void init_led( void )
{
	pwm_start();
	UTICK_SetTick( UTICK0, kUTICK_Repeat, 10000 - 1, led_control_callback );
}

void led_set_color( float temp, float ref )
{
	if ( (ref + 2) < temp )
	{
		target	= red;
	}
	else if ( (ref + 1) < temp )
	{
		target	= green;
	}
	else
	{
		target	= blue;
	}
	
	trigger	= PIN_LED_OFF;
}

void led_all( bool v )
{
	red		= v;
	green	= v;
	blue	= v;
}

void led_pin_control( int v )
{
	static const int k	= 32;
	
	v	%= k;
	if ( v < (k - 5) )
		led_all( PIN_LED_OFF );
	else
		trigger	= true;
}


void trigger_output( void )
{
	trigger	= false;
}
