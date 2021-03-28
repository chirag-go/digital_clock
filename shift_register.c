/*
 * shift_register.c
 *
 * Created: 28-03-2021 09:49:22
 *  Author: Chirag Goyal
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

/*
 *		Definitons regarding the shift register
 */
#define SR_PORT		PORTD
#define SR_DDR		DDRD

#define SR_DATA		PD0
#define SR_CLOCK	PD1
#define SR_LATCH	PD2
#define SR_RST		PD3

/*
 *	This function displays the data on its 8 bit output
 */
void shift(uint8_t x)
{
	uint8_t d;
	for(uint8_t i=0 ;i<8;i++){
		d = ((x>>i)&1);
		if(d==0)	SR_PORT &= ~(1<<SR_DATA);
		else		SR_PORT |= (1<<SR_DATA);
		SR_PORT |= (1<<SR_CLOCK);
		SR_PORT &= ~(1<<SR_CLOCK);
		
	}
	SR_PORT |= (1<<SR_LATCH);
	SR_PORT &= ~(1<<SR_LATCH);
}
int main(void)
{
	DDRA = 255;
	SR_DDR |= ((1<<SR_CLOCK)|(1<<SR_DATA)|(1<<SR_LATCH)|(1<<SR_RST));
	while (1)
	{
		shift(24);
		_delay_ms(1000);
		shift(21);
		_delay_ms(1000);
	}	
}
