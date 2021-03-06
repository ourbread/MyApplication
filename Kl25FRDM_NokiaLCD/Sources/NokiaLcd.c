/*
 * NokiaLcd.c
 *
 *  Created on: Jul 22, 2014
 *      Author: YE RUIYUAN
 */

#include "NokiaLcd.h"

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


//6x8.h文件：
/*-----------------------------------------------
6 x 8 font
1 pixel space at left and bottom
index = ASCII - 32
-----------------------------------------------*/
const unsigned char  font6x8[][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },// sp
{ 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },// !
{ 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },// "
{ 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },// #
{ 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },// $
{ 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },// %
{ 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },// &
{ 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },// '
{ 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },// (
{ 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },// )
{ 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },// *
{ 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },// +
{ 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },// ,
{ 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },// -
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },// .
{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },// /
{ 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },// 0
{ 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },// 1
{ 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },// 2
{ 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },// 3
{ 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },// 4
{ 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },// 5
{ 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },// 6
{ 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },// 7
{ 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },// 8
{ 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },// 9
{ 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },// :
{ 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },// ;
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },// <
{ 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },// =
{ 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },// >
{ 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },// ?
{ 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },// @
{ 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },// A
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },// B
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },// C
{ 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },// D
{ 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },// E
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },// F
{ 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },// G
{ 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },// H
{ 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },// I
{ 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },// J
{ 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },// K
{ 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },// L
{ 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },// M
{ 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },// N
{ 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },// O
{ 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },// P
{ 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },// Q
{ 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },// R
{ 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },// S
{ 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },// T
{ 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },// U
{ 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },// V
{ 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },// W
{ 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },// X
{ 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },// Y
{ 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },// Z
{ 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },// [
{ 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },// 55
{ 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },// ]
{ 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },// ^
{ 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },// _
{ 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },// '
{ 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },// a
{ 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },// b
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },// c
{ 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },// d
{ 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },// e
{ 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },// f
{ 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },// g
{ 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },// h
{ 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },// i
{ 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },// j
{ 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },// k
{ 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },// l
{ 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },// m
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },// n
{ 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },// o
{ 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },// p
{ 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },// q
{ 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },// r
{ 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },// s
{ 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },// t
{ 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },// u
{ 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },// v
{ 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },// w
{ 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },// x
{ 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },// y
{ 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },// z
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }// horiz lines
}; 

const unsigned char shuzi[]={
/*--  文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,

/*--  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

/*--  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

/*--  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,

/*--  文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

/*--  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,

/*--  文字:  a  --10*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,

/*--  文字:  b  --11*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  c  --12*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,

/*--  文字:  d  --13*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,

/*--  文字:  e  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,

/*--  文字:  f  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

/*--  文字:  g  --16*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,

/*--  文字:  h  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,

/*--  文字:  i  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

/*--  文字:  j  --19*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,

/*--  文字:  k  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,

/*--  文字:  l  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,

/*--  文字:  m  --22*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,

/*--  文字:  n  --23*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,

/*--  文字:  o  --24*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,

/*--  文字:  p  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  q  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,

/*--  文字:  r  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,
																			   
/*--  文字:  s  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,

/*--  文字:  t  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,

/*--  文字:  u  --30*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,

/*--  文字:  v  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,

/*--  文字:  w  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,

/*--  文字:  x  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,

/*--  文字:  y  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,

/*--  文字:  z  --35*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,

/*--  文字:  -  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,

/*--  文字:  =  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  \  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,

/*--  文字:     --39*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  [  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,

/*--  文字:  ]  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,

/*--  文字:  ;  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,

/*--  文字:  '  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  ,  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  .  --45*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  /  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,

};

const unsigned char han[]=
{
		
		/*--  文字:  叶  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0xFC,0x04,0x04,0xFC,0x00,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0x00,
		0x00,0x0F,0x04,0x04,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,

		/*--  文字:  瑞  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x84,0x84,0xFC,0x84,0x84,0x40,0x5E,0x50,0x50,0x50,0xDF,0x50,0x50,0x50,0x5E,0x00,
		0x10,0x30,0x1F,0x08,0x08,0x00,0xFE,0x02,0x02,0x7F,0x02,0x7E,0x02,0x82,0xFE,0x00,

		/*--  文字:  源  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x60,0x02,0x8C,0x00,0xFE,0x02,0xF2,0x52,0x5A,0x56,0x52,0x52,0xF2,0x02,0x00,
		0x04,0x04,0x7E,0x41,0x30,0x0F,0x20,0x13,0x49,0x81,0x7F,0x01,0x09,0x13,0x20,0x00,
		
		
		/*--  文字:  陆  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0xFE,0x02,0x22,0xDA,0x06,0x80,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x80,0x00,
		0x00,0xFF,0x08,0x10,0x08,0x07,0x00,0x7C,0x40,0x40,0x7F,0x40,0x40,0xFC,0x00,0x00,

		/*--  文字:  舜  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x00,0x60,0x22,0x2A,0xF2,0x22,0x22,0x26,0x3A,0x21,0x21,0xF1,0x2D,0x21,0x60,0x00,
		0x00,0x84,0x42,0x25,0x19,0x09,0x07,0x00,0x1D,0x11,0x11,0xFF,0x11,0x11,0x10,0x00,

		/*--  文字:  桦  --*/
		/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
		0x10,0x10,0xD0,0xFF,0x90,0x20,0x10,0xFC,0x03,0x40,0x20,0x7F,0x88,0x86,0xE0,0x00,
		0x04,0x03,0x00,0xFF,0x00,0x01,0x04,0x05,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x00,

};

const unsigned char pic[]=
{
	/*--  调入了一幅图像：C:\Users\YE RUIYUAN\Desktop\5110 液晶屏资料\图片文件\4.bmp  --*/
	/*--  宽度x高度=40x40  --*/
		0xE0,0x1C,0x06,0x01,0x01,0x03,0x02,0x02,0x84,0x04,0x08,0x10,0x30,0x20,0xC0,0x80,
		0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x70,0x18,0x04,0x84,0x86,0x42,0xC2,0x42,0x82,
		0xC2,0x82,0x84,0x0C,0x08,0x30,0xC0,0x00,0xF5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0xEB,0xD8,0x60,0x60,0x10,0x18,0x18,0x05,0x0D,0x06,0x04,0x06,0x02,0x06,0x83,0x46,
		0x84,0x86,0x0D,0x09,0x0C,0x18,0x38,0x28,0x50,0xD3,0xAA,0x3F,0x3C,0xB0,0x02,0xFD,
		0x03,0x06,0x0C,0x08,0x08,0xEC,0x3C,0x07,0x03,0x01,0x00,0x00,0x38,0x6C,0xE4,0x7C,
		0x70,0x00,0x00,0xE0,0xE0,0xE2,0xC7,0x0E,0x0E,0x0F,0x00,0x00,0xC0,0x70,0x00,0x00,
		0x00,0x00,0x02,0x01,0x03,0x04,0xAB,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x40,
		0x00,0x00,0x00,0x08,0x10,0x10,0x10,0x30,0x30,0x70,0x70,0xF0,0xF3,0xFB,0x8D,0x04,
		0x84,0x8C,0xFE,0xFF,0xDF,0x01,0x00,0x00,0x00,0x80,0xC0,0xE0,0xB0,0x1A,0x06,0x01,
		0x00,0x00,0x00,0x02,0x07,0x0D,0x09,0x14,0x10,0x28,0x30,0x20,0x20,0x20,0x20,0x20,
		0x20,0x20,0x20,0x60,0xA1,0xA3,0x97,0x97,0xFF,0xBD,0x8D,0x8F,0x87,0x84,0x82,0x41,
		0x41,0x40,0x20,0xE0,0x80,0x81,0x86,0xFC,
};

//---------------------------------------
//名称: 使用SPI接口写数据到LCD
//参数：dt：写入的数据 command: 1-数据/0-命令
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//-----------------------------------------  
void LCD_write_byte(unsigned char dt, unsigned char command)
{
	unsigned char i;  	
    sce0; 	
	if(command)
		dc1;
	else
		dc0;		
	for(i=0;i<8;i++)
	{ 
		if(dt&0x80)
			sdin1;
		else
			sdin0;
		dt=dt<<1;	
		sclk0; 	
		WAIT1_Wait100Cycles();
		sclk1; 	
		WAIT1_Wait100Cycles();
	}
	sce1; 
}
//---------------------------------------
//名称: 5110LCD初始化函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//----------------------------------------- 
void LCD_init(void)
{
	sce1;
	res1;
	WAIT1_Waitms(10);
	res0;  	
	WAIT1_Waitms(100);
  	res1;  
  	WAIT1_Waitms(10);
	LCD_write_byte(0x21,0);//LCD功能设置：芯片活动，水平寻址，使用扩展指令
	//LCD_write_byte(0xd0,0);//设置VOP值，室温下的编程范围为3.00-10.68
	//Vlcd=3.06+(VOP)*0.06,本例VOP为0B0101 0000为十进制的80，Vlcd=7.86V
	LCD_write_byte(0xee,0);
	LCD_write_byte(0x20,0);//LCD功能设置：芯片活动，水平寻址，使用基本指令
	LCD_write_byte(0x0C,0);//设定显示配置:普通模式
	sce1;
}
//---------------------------------------
//名称: 设置坐标函数
//参数：X：0－83 Y：0－5
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//-----------------------------------------   
void LCD_set_XY(unsigned char X, unsigned char Y)
{
	LCD_write_byte(0x40 | Y, 0);// column
	LCD_write_byte(0x80 | X, 0);// row
	sce1;
} 
//---------------------------------------
//名称: LCD清屏函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//----------------------------------------- 
void LCD_clear(void)
{
	unsigned char t;
	unsigned char k;
	LCD_set_XY(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			LCD_write_byte(0x00,1);	 						
		} 
	}
	sce1;
}
//---------------------------------------
//名称: 显示英文字符
//参数：c：显示的字符在font6x8表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//-----------------------------------------  	
void LCD_write_char(unsigned char c)
{
	unsigned char line;
	c-= 32;
	for (line=0; line<6; line++)
	LCD_write_byte(font6x8[c][line], 1);
}
//---------------------------------------
//名称: 英文字符串显示函数
//参数：*s：英文字符串指针
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//-----------------------------------------  
void LCD_write_String(unsigned char X,unsigned char Y,char *s)
{
	LCD_set_XY(X,Y);
	while (*s) 
	{
		LCD_write_char(*s);
		s++;
	}
} 
//---------------------------------------
//名称: 写一个字符到LCD函数（8*16点阵）
//参数：row,page：写入字符的地址 c: 写入字符在shuzi表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
void LCD_write_shu(unsigned char row, unsigned char page,unsigned char c) //row:列 page:页 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*8, page);// 列，页 
	for(i=0; i<8;i++) 
	{
		LCD_write_byte(shuzi[c*16+i],1); 
	}
	
    LCD_set_XY(row*8, page+1);// 列，页 
	for(i=8; i<16;i++) 
	{
		LCD_write_byte(shuzi[c*16+i],1);
	}
	sce1;
}
//---------------------------------------
//名称: 写一个汉字到LCD函数
//参数：x,y：写入汉字的地址 address: 写入汉字在han表格中的位置
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081111  
//----------------------------------------- 
void LCD_write_hanzi(unsigned char row, unsigned char page,unsigned char c) //row:列 page:页 dd:字符
{
	unsigned char i;  	
	
	LCD_set_XY(row*8, page);// 列，页 
	for(i=0; i<16;i++) 
	{
		LCD_write_byte(han[c*32+i],1); 
	}

    LCD_set_XY(row*8, page+1);// 列，页 
	for(i=16; i<32;i++) 
	{
		LCD_write_byte(han[c*32+i],1);
	}	
	sce1;
}



void LCD_write_pic_40x40(void)
{
	unsigned char i;  	
	
	LCD_set_XY(0, 1);
	for(i=0; i<40;i++) 
	{
		LCD_write_byte(pic[i],1); 
	}

    LCD_set_XY(0, 2);
	for(i=40; i<80;i++) 
	{
		LCD_write_byte(pic[i],1);
	}
	
    LCD_set_XY(0, 3);
	for(i=80; i<120;i++) 
	{
		LCD_write_byte(pic[i],1);
	}

    LCD_set_XY(0, 4);
	for(i=120; i<160;i++) 
	{
		LCD_write_byte(pic[i],1);
	}
	
    LCD_set_XY(0, 5);
	for(i=160; i<200;i++) 
	{
		LCD_write_byte(pic[i],1);
	}
	
	sce1;
}
