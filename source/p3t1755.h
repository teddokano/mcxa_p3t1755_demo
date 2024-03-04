/*
 * Copyright 2024 Tedd OKANO
 */

#include	"i3c/i3c.h"

#define P3T1755_ADDR_I2C			0x48U
#define P3T1755_ADDR_I3C			0x08U
#define P3T1755_CONFIG_VALUE		0x2A

class P3T1755 {
public:
	enum	registers {
		Temp,
		Conf,
		T_LOW,
		T_HIGH,
	};

	P3T1755( I3C &i3c, uint8_t address = 0x48 );
	~P3T1755();
	
	float		temp( void );
	
	void		conf( uint8_t conf );
	uint8_t		conf( void );
	
	void		high( float temp );
	float		high( void );
	
	void		low(  float temp );
	float		low(  void );

	void 		write( uint8_t reg, float v );
	int16_t 	read( uint8_t reg );

	void		ccc_set( uint8_t ccc, uint8_t data );
	uint8_t*	ccc_get( uint8_t ccc, uint8_t *dp, uint8_t length );

	static float	short2celsius( int16_t v );
	static int16_t	celsius2short( float v );
	static int16_t	swap_bytes( int16_t v );

	/** A short hand for reading pins
	 */
	operator	float();

private:
	I3C&	_i3c;
	uint8_t	_addr;
};
