/*
 * DHT11.c
 *
 *  Created on: Jul 22, 2014
 *      Author: YE RUIYUAN
 */
#include "DHT11.h"

#include "DHT.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "PE_Types.h"

#include "CsIO1.h"
#include "IO1.h"

byte dht11_dat[5];

byte read_dht11_dat() {
	byte j = 0;
	byte result = 0;
	for (j = 0; j < 8; j++) {
		while (!DHT_GetVal());//while (!(PINC & _BV(DHT11_PIN))); // wait for 50us
		WAIT1_Waitus(30);//delayMicroseconds(30);
		if (DHT_GetVal())//if (PINC & _BV(DHT11_PIN))
		{
			result |= (1 << (7 - j));
			while (DHT_GetVal());//while ((PINC & _BV(DHT11_PIN))); // wait '1' finish
		}
	}
	return result;
}

void DHT11() {
	
	byte dht11_in;
	byte i;
	
	// output
	DHT_SetDir(1);
	// pull-down i/o pin for 18ms
	DHT_ClrVal();
	WAIT1_Waitms(19);
	DHT_SetVal();
	//pull-up i/o pin for 30ms
	WAIT1_Waitus(30);

	//input
	DHT_SetDir(0);
	
	WAIT1_Waitus(30);

	while(!dht11_in)
	{
		dht11_in = DHT_GetVal();//dht11_in = PINC & _BV(DHT11_PIN);
	}
//	if (dht11_in) {
//		printf("dht11 start condition 1 not met\r\n");
//		return;
//	}
	WAIT1_Waitus(80);//delayMicroseconds(80);
//	dht11_in = DHT_GetVal();//dht11_in = PINC & _BV(DHT11_PIN);
//	if (!dht11_in) {
//		printf("dht11 start condition 2 not met\r\n");
//		return;
//	}
//	WAIT1_Waitus(80);//delayMicroseconds(80);
	// now ready for data reception
	for (i = 0; i < 5; i++)
		dht11_dat[i] = read_dht11_dat();
	DHT_SetDir(1);//DDRC |= _BV(DHT11_PIN);
	DHT_SetVal();//PORTC |= _BV(DHT11_PIN);
	byte dht11_check_sum = dht11_dat[0] + dht11_dat[1] + dht11_dat[2]
			+ dht11_dat[3];
	// check check_sum
	if (dht11_dat[4] != dht11_check_sum) {
		printf("DHT11 checksum error\r\n");
	}
	
	printf("Current humdity = ");
	printf("%d",dht11_dat[0]);
	printf(".");
	printf("%d",dht11_dat[1]);
	printf("%%\r\n");
	printf("temperature = ");
	printf("%d",dht11_dat[2]);
	printf(".");
	printf("%d",dht11_dat[3]);
	printf("C \r\n");
//	WAIT1_Waitms(2000);//delay(2000);
}
