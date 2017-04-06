#include<avr/io.h>
#define F_CPU 16000000UL // internal clock
#include <util/delay.h>
#include<avr/interrupt.h>
#include<string.h>

#define F_CPU 16000000UL  // 16 MHz
#include<avr/io.h>
#include<avr/interrupt.h>

#define UART_BAUDRATE 38400
#define BAUD_VALUE (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)






volatile unsigned char value;





ISR(USART_RXC_vect) 
{

	UCSRA=0X80;
	value = UDR;	

	if (value=='N')
	{
	
		PORTA |= _BV(PORTA0) ;
		PORTA |= _BV(PORTA1) ; 
		PORTA |= _BV(PORTA2) ;
		PORTA |= _BV(PORTA3) ; 
	
	
	
	}
	else if (value =='F')
	{
	
		PORTA |= _BV(PORTA0) ;
		PORTA &= ~_BV(PORTA1) ; 
		PORTA |= _BV(PORTA2) ;
		PORTA &= ~_BV(PORTA3); 
			
	

	}
	else if (value =='B')
	{
		PORTA &= ~_BV(PORTA0) ;
		PORTA |= _BV(PORTA1) ; 
		PORTA &= ~_BV(PORTA2) ;
		PORTA |= _BV(PORTA3) ; 
	
		
	}
	else if (value =='L')
	{
		PORTA &= ~_BV(PORTA0) ;
		PORTA |= _BV(PORTA1) ; 
		PORTA |= _BV(PORTA2) ;
		PORTA |= _BV(PORTA3) ; 
		
		
	}
	else if (value =='R')
	{
		PORTA |= _BV(PORTA0) ;
		PORTA |= _BV(PORTA1) ; 
		PORTA &= ~_BV(PORTA2) ;
		PORTA |= _BV(PORTA3) ; 
	
	
	
	}
	else
	{
		PORTA &= ~_BV(PORTA0) ;
		PORTA &= ~_BV(PORTA1) ; 
		PORTA &= ~_BV(PORTA2) ;
		PORTA &= ~_BV(PORTA3) ; 
	
		_delay_ms(1000);			
	}	

	

	while((UCSRA&0X80)==0);

}
   


int main (void)
{
DDRA = 0xFF; 
 
 
UBRRL = (BAUD_VALUE);
	UBRRH = (BAUD_VALUE >> 8);

	//UCSRA=UCSRB=UCSRC=0x00;						// Usart Control & Status Register A,B,C Clear
	UCSRB = ((1<<RXEN) | (1<<RXCIE));	// Enable transmission and reception and
	// reception interrupt
	UCSRC=((1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0));	// Usart Control & Status register C enable
	
	//	and setting 8-bit mode

	sei();         // Global interrupt Enable
	 while(1);

 } //main
 	
