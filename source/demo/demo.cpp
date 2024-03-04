/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"config.h"

extern "C" {

#include	"fsl_debug_console.h"

#include	"demo/led_control.h"
#include	"demo/pin.h"
#include	"p3t1755.h"
}

#include	"i3c.h"
#include	"demo.h"

void trigger_output( void );

extern	I3C	i3c;

void init_demo( void )
{
	init_led();
	i3c.set_IBI_callback( trigger_output );
}

void demo( float temp, float *ref_temp_ptr )
{
	led_set_color( temp, *ref_temp_ptr );
}

void trigger_output( void )
{
	pin_write( IBI_TRIGGER_OUTPUT, false );
}
