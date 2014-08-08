/*
 * NokiaLcd.h
 *
 *  Created on: Jul 22, 2014
 *      Author: YE RUIYUAN
 */

#ifndef NOKIALCD_H_
#define NOKIALCD_H_

//platform: kl25 freedom board
#define sce0   SCE_ClrVal()
#define res0   RES_ClrVal()
#define dc0   DC_ClrVal()
#define sdin0  MOSI_ClrVal()
#define sclk0  CLK_ClrVal()
#define backled0     BL_ClrVal()

#define sce1   SCE_SetVal()
#define res1   RES_SetVal()  
#define dc1    DC_SetVal() 
#define sdin1  MOSI_SetVal() 
#define sclk1  CLK_SetVal() 
#define backled1   BL_SetVal()


extern const unsigned char  font6x8[][6];
extern const unsigned char shuzi[];
extern const unsigned char han[];

void LCD_write_byte(unsigned char dt, unsigned char command);

void LCD_init(void);

void LCD_set_XY(unsigned char X, unsigned char Y);

void LCD_clear(void);
	
void LCD_write_char(unsigned char c);
 
void LCD_write_String(unsigned char X,unsigned char Y,char *s);

void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符

void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符

void LCD_write_pic_40x40(void);



#endif /* NOKIALCD_H_ */
