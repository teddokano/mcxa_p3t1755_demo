/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_INTERRUPTIN_H
#define R01LIB_INTERRUPTIN_H

extern "C" {
#include	"fsl_utick.h"
}

#include	"io.h"


class InterruptIn : public DigitalIn
{	
public:
	InterruptIn( uint8_t pin_num );
	~InterruptIn();
	
	void	fall( utick_callback_t callback );
};

#endif // R01LIB_INTERRUPTIN_H
