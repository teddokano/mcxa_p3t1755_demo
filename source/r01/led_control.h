/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

void	init_led( void );
//void	init_led( DigitalOut &r, DigitalOut &g, DigitalOut &b, DigitalOut &t, DigitalOut &trig );

void	led_set_color( float temp, float ref );
void	led_all( bool v );
void	led_pin_control( int v );

void	trigger_output( void );

