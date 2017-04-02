/*
 * adxl_for_vehicle.c
 *
 * Created: 4/25/2016 7:37:57 PM
 *  Author: welcome
 */ 




#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#define UART_BAUDRATE 38400
#define BAUD_VALUE (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)




void send_char(volatile unsigned char c){

	UCSRA = 0x40;
	UDR=c;
	while((UCSRA&0X40)==0);
}

void prints(char *ptr){
	while(*ptr)	{
		send_char(*ptr);
		ptr++;
	}
}

int read_adc(char chnl){
	int val,val1;
	ADMUX= 0x40;
	ADCSRA=0x86;   		// ADC enable and prescalar set to 64 for ADC clock 125KHz
	ADMUX=(0x40|(chnl&0x07));	// Reference voltage selection, result right justified, Channel 0 selection
	_delay_ms(1);
	ADCSRA|=0x40;				// ADC Convertion start
	while((ADCSRA & 0x40));	// wait for conversion to complete
	val = ADCL;
	val1 = ADCH;
	val |= (val1<<8);
	return(val);
}

int main(){
	int adc_val=0,adc_val1=0,adc_val2=0,adc_val01=0,adc_val02=0,adc_val03=0,adc_val04=0,adc_val11=0,adc_val12=0,adc_val13=0,adc_val14=0,ck1=0,ck2=0;
	UBRRL = (BAUD_VALUE);
	UBRRH = (BAUD_VALUE >> 8);

	UCSRA=UCSRB=UCSRC=0x00;		// Usart Control & Status Register A,B,C Clear
	UCSRB=0X08;			// Transmission Enable
	UCSRC=0X86;
	adc_val01=read_adc(0);
	_delay_ms(2);
	adc_val02=read_adc(0);
	_delay_ms(2);
	adc_val03=read_adc(0);
	_delay_ms(2);
	adc_val04=read_adc(0);
	_delay_ms(2);
	ck1=((adc_val01+adc_val02+adc_val03+adc_val04)/4);
	adc_val11=read_adc(1);
	_delay_ms(2);
	adc_val12=read_adc(1);
	_delay_ms(2);
	adc_val13=read_adc(1);
	_delay_ms(2);
	adc_val14=read_adc(1);
	_delay_ms(2);
	ck2=((adc_val11+adc_val12+adc_val13+adc_val14)/4);
	

	while(1){
		adc_val=read_adc(0);
		adc_val1=read_adc(1);
		if (adc_val>(ck1+10))
		send_char('R');
		else if(adc_val<(ck1-10))
		send_char('L');
		else if (adc_val1>(ck2+10))
		send_char('F');
		else if(adc_val1<(ck2-10))
		send_char('B');
		else 
		send_char('N');
	}
}


