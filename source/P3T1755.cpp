#include	"i3c/i3c.h"
#include	"P3T1755.h"

P3T1755::P3T1755( I3C &i3c, uint8_t address ) : _i3c( i3c ), _addr( address ) {}
P3T1755::~P3T1755(){}

float P3T1755::temp( void )
{
	return short2celsius( read( Temp ) );
}

void P3T1755::conf( uint8_t config )
{
	_i3c.reg_write( _addr, Conf, &config, sizeof( config ) );
}

uint8_t P3T1755::conf( void )
{
	uint8_t	c;
	_i3c.reg_read( _addr, P3T1755::Conf, &c, sizeof( c ) );
	
	return c;
}

void P3T1755::high( float celsius )
{
	write( T_HIGH, celsius );
}

float P3T1755::high( void )
{
	return short2celsius( read( T_HIGH ) );
}

void P3T1755::low( float celsius )
{
	write( T_LOW, celsius );
}

float P3T1755::low( void )
{
	return short2celsius( read( T_LOW ) );
}

void P3T1755::write( uint8_t reg, float v )
{
	uint16_t	tmp	= swap_bytes( celsius2short( v ) );
	_i3c.reg_write( _addr, reg, (uint8_t *)&tmp, sizeof( tmp ) );
}

int16_t P3T1755::read( uint8_t reg )
{
	uint16_t	tmp;
	_i3c.reg_read( _addr, reg, (uint8_t *)&tmp, sizeof( tmp ) );
	
	return tmp;
}

void P3T1755::ccc_set( uint8_t ccc, uint8_t data )
{
	_i3c.ccc_set( ccc, _addr, data );
}

uint8_t* P3T1755::ccc_get( uint8_t ccc, uint8_t *dp, uint8_t length )
{
	_i3c.ccc_get( ccc, _addr, dp, length );
	
	return dp;
}

float P3T1755::short2celsius( int16_t v )
{
	return (float)(swap_bytes( v )) / 256.0;
}

int16_t P3T1755::celsius2short( float v )
{
	return (uint16_t)(v * 256.0);
}

int16_t	P3T1755::swap_bytes( int16_t v )
{
#ifdef __BIG_ENDIAN__
	return v;
#else	
	return (v << 8) | ((uint16_t)v >> 8);
#endif
}

P3T1755::operator float()
{
	return temp();
}

