#include	"r01lib.h"
r01lib_start;

I3C			i3c;
P3T1755		p3t1755( i3c );

int main(void)
{
	float	temp;

	i3c.ccc_broadcast( CCC::BROADCAST_RSTDAA, NULL, 0 );
	i3c.ccc_set( CCC::DIRECT_SETDASA, 0x48, 0x08 << 1 );
	p3t1755.address_overwrite( 0x08 );

	while ( true )
	{
		temp	= p3t1755;
		PRINTF( "Temperature: %8.4f˚C\r\n", temp );
		wait( 1 );
	}
}

