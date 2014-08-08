/* ###################################################################
**     Filename    : main.c
**     Project     : Kl25FRDM_NokiaLCD
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-07-22, 20:05, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "RES.h"
#include "BitIoLdd1.h"
#include "SCE.h"
#include "BitIoLdd2.h"
#include "DC.h"
#include "BitIoLdd3.h"
#include "MOSI.h"
#include "BitIoLdd4.h"
#include "CLK.h"
#include "BitIoLdd5.h"
#include "BL.h"
#include "BitIoLdd6.h"
#include "DHT.h"
#include "BitIoLdd7.h"
#include "CsIO1.h"
#include "IO1.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "NokiaLcd.h"
#include "DHT11.h"

extern byte dht11_dat[5];

byte strTmp1[24];
byte strTmp2[24];


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
	LCD_init();	
	LCD_clear();
	backled1;	
	
	//LCD_write_String(3,3,"hello baby!");	
	
//	LCD_write_hanzi(2,1,0);
//	LCD_write_hanzi(4,1,1);
//	LCD_write_hanzi(6,1,2);	
//	LCD_write_hanzi(2,4,3);
//	LCD_write_hanzi(4,4,4);
//	LCD_write_hanzi(6,4,5);
	
	LCD_write_pic_40x40();
	
//	LCD_write_String(3,3,"hello baby!");	
	
	for(;;)
	{
		WAIT1_Waitms(3000);
	    DHT11();	

	    UTIL1_strcpy(strTmp1, 4 ,(byte *)"H= ");
		UTIL1_Num8uToStr(strTmp2, sizeof(strTmp2),dht11_dat[0]);
		UTIL1_strcat(strTmp1, sizeof(strTmp1),strTmp2);			
		//UTIL1_strcat(strTmp1, sizeof(strTmp1),(byte *)".");
		//UTIL1_Num8uToStr(strTmp2, sizeof(strTmp2),dht11_dat[1]);
		//UTIL1_strcat(strTmp1, sizeof(strTmp1),strTmp2);
		UTIL1_strcat(strTmp1, sizeof(strTmp1),(byte *)"%");

		LCD_write_String(45,2,(char *)strTmp1);	
		
	    UTIL1_strcpy(strTmp1, 4 ,(byte *)"T= ");
		UTIL1_Num8uToStr(strTmp2, sizeof(strTmp2),dht11_dat[2]);
		UTIL1_strcat(strTmp1, sizeof(strTmp1),strTmp2);			
		//UTIL1_strcat(strTmp1, sizeof(strTmp1),(byte *)".");
		//UTIL1_Num8uToStr(strTmp2, sizeof(strTmp2),dht11_dat[3]);
		//UTIL1_strcat(strTmp1, sizeof(strTmp1),strTmp2);
		UTIL1_strcat(strTmp1, sizeof(strTmp1),(byte *)"C");

		LCD_write_String(45,4,(char *)strTmp1);	
	
	}
	
	
	

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
