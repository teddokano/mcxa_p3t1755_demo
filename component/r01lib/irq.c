#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"

#include	"irq.h"

void GPIO0_IRQHandler( void )
{	irq_handler( 0 );
}

void GPIO1_IRQHandler( void )
{	irq_handler( 1 );
}

void GPIO2_IRQHandler( void )
{	irq_handler( 2 );
}

void GPIO3_IRQHandler( void )
{
	irq_handler( 3 );
}
