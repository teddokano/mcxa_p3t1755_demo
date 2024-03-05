/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define	PIN_OUTPUT			kGPIO_DigitalOutput
#define	PIN_INPUT			kGPIO_DigitalInput

#define	DISABLED_GPIO		(GPIO_Type *)NULL
#define	DISABLED_PIN		0xFF

#define RED_GPIO			BOARD_LED_RED_GPIO
#define GREEN_GPIO			BOARD_LED_GREEN_GPIO
#define BLUE_GPIO			BOARD_LED_BLUE_GPIO

#define RED_GPIO_PIN		BOARD_LED_RED_GPIO_PIN
#define GREEN_GPIO_PIN		BOARD_LED_GREEN_GPIO
#define BLUE_GPIO_PIN		BOARD_LED_BLUE_GPIO

#define D0_GPIO				BOARD_INITPINS_ARD_D0_GPIO
#define D1_GPIO				BOARD_INITPINS_ARD_D1_GPIO
#define D2_GPIO				BOARD_INITPINS_ARD_D2_GPIO
#define D3_GPIO				BOARD_INITPINS_ARD_D3_GPIO	//	BLUE
#define D4_GPIO				BOARD_INITPINS_ARD_D4_GPIO
#define D5_GPIO				BOARD_INITPINS_ARD_D5_GPIO	//	RED
#define D6_GPIO				BOARD_INITPINS_ARD_D6_GPIO	//	GREEN
#define D7_GPIO				BOARD_INITPINS_ARD_D7_GPIO
#define D8_GPIO				BOARD_INITPINS_ARD_D8_GPIO
#define D9_GPIO				BOARD_INITPINS_ARD_D9_GPIO
#define D10_GPIO			BOARD_INITPINS_ARD_D10_GPIO
#define D11_GPIO			BOARD_INITPINS_ARD_D11_GPIO
#define D12_GPIO			BOARD_INITPINS_ARD_D12_GPIO
#define D13_GPIO			BOARD_INITPINS_ARD_D13_GPIO
#define D18_GPIO			BOARD_INITPINS_ARD_D18_GPIO
#define D19_GPIO			BOARD_INITPINS_ARD_D19_GPIO
#define A0_GPIO				BOARD_INITPINS_ARD_A0_GPIO
#define A1_GPIO				BOARD_INITPINS_ARD_A1_GPIO
#define A2_GPIO				BOARD_INITPINS_ARD_A2_GPIO
#define A3_GPIO				BOARD_INITPINS_ARD_A3_GPIO
#define A4_GPIO				BOARD_INITPINS_ARD_A4_GPIO
#define A5_GPIO				BOARD_INITPINS_ARD_A5_GPIO


#define D0_GPIO_PIN			BOARD_INITPINS_ARD_D0_GPIO_PIN
#define D1_GPIO_PIN			BOARD_INITPINS_ARD_D1_GPIO_PIN
#define D2_GPIO_PIN			BOARD_INITPINS_ARD_D2_GPIO_PIN
#define D3_GPIO_PIN			BOARD_INITPINS_ARD_D3_GPIO_PIN
#define D4_GPIO_PIN			BOARD_INITPINS_ARD_D4_GPIO_PIN
#define D5_GPIO_PIN			BOARD_INITPINS_ARD_D5_GPIO_PIN
#define D6_GPIO_PIN			BOARD_INITPINS_ARD_D6_GPIO_PIN
#define D7_GPIO_PIN			BOARD_INITPINS_ARD_D7_GPIO_PIN
#define D8_GPIO_PIN			BOARD_INITPINS_ARD_D8_GPIO_PIN
#define D9_GPIO_PIN			BOARD_INITPINS_ARD_D9_GPIO_PIN
#define D10_GPIO_PIN		BOARD_INITPINS_ARD_D10_GPIO_PIN
#define D11_GPIO_PIN		BOARD_INITPINS_ARD_D11_GPIO_PIN
#define D12_GPIO_PIN		BOARD_INITPINS_ARD_D12_GPIO_PIN
#define D13_GPIO_PIN		BOARD_INITPINS_ARD_D13_GPIO_PIN
#define D18_GPIO_PIN		BOARD_INITPINS_ARD_D18_GPIO_PIN
#define D19_GPIO_PIN		BOARD_INITPINS_ARD_D19_GPIO_PIN
#define A0_GPIO_PIN			BOARD_INITPINS_ARD_A0_GPIO_PIN
#define A1_GPIO_PIN			BOARD_INITPINS_ARD_A1_GPIO_PIN
#define A2_GPIO_PIN			BOARD_INITPINS_ARD_A2_GPIO_PIN
#define A3_GPIO_PIN			BOARD_INITPINS_ARD_A3_GPIO_PIN
#define A4_GPIO_PIN			BOARD_INITPINS_ARD_A4_GPIO_PIN
#define A5_GPIO_PIN			BOARD_INITPINS_ARD_A5_GPIO_PIN

/*
 *	Following pins are disabled since the pins are assigned to other function
 */
#undef	BOARD_INITPINS_ARD_D3_GPIO
#undef	BOARD_INITPINS_ARD_D3_GPIO_PIN
#define	BOARD_INITPINS_ARD_D3_GPIO		DISABLED_GPIO
#define	BOARD_INITPINS_ARD_D3_GPIO_PIN	DISABLED_PIN

enum { 	D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D18, D19,
		A0, A1, A2, A3, A4, A5 };

#define	RED		D5
#define	GREEN	D6
#define	BLUE	D3

#define	PIN_LED_OFF	true
#define	PIN_LED_ON	false

class DigitalInOut
{
public:
	DigitalInOut( uint8_t pin_num, bool direction = kGPIO_DigitalInput, bool value = 0 );
	~DigitalInOut();
	
	void	value( bool value );
	bool	value( void );
	
	void	output( void );
	void	input( void );
	
	/** A short hand for setting pins
	 */
	DigitalInOut&	operator=( bool v );
	DigitalInOut&	operator=( DigitalInOut& rhs );

	/** A short hand for reading pins
	 */
	operator	bool();

private:
	uint8_t	_pn; 
	bool 	_dir; 
	bool 	_value;
};

class DigitalOut : public DigitalInOut
{
public:
	using DigitalInOut::operator=;

	DigitalOut( uint8_t pin_num, bool value = 0 );
	~DigitalOut();
};

class DigitalIn : public DigitalInOut
{
public:
	using DigitalInOut::operator=;

	DigitalIn( uint8_t pin_num );
	~DigitalIn();
};

