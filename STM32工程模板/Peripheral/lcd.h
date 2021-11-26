#ifndef __LCD_
#define __LCD_
//#include "Include.h"
#include "stdlib.h"
#include "delay.h"
#include "sys.h"

#define USE_HORIZONTAL 0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 240
#endif

//-----------------LCD端口定义----------------
//DATAOUT 这个可以琢磨琢磨这么个用法
#define DATAOUT(x) GPIOF->ODR=((GPIOF->ODR&0xffffff00)|x)//8位数据并口输出 bit0-7

#define LCD_BKL_ON  PAout(7)=1		//背光LED   PA7
#define	LCD_RST_SET	PFout(11)=1     //复位		PF11
#define	LCD_CS_SET  PFout(12)=1     //片选端口  	PF12
#define	LCD_DC_SET	PFout(13)=1     //数据/命令  PF13
#define	LCD_WR_SET	PFout(14)=1     //写数据	    PF14
#define	LCD_RD_SET	PFout(15)=1     //读数据		PF15

#define LCD_BKL_OFF PAout(7)=0		//背光LED   PA7
#define	LCD_RST_CLR	PFout(11)=0     //复位		PF11			    
#define	LCD_CS_CLR  PFout(12)=0     //片选端口  PF12
#define	LCD_DC_CLR	PFout(13)=0     //数据/命令 PF13
#define	LCD_WR_CLR	PFout(14)=0     //写数据	PF14
#define	LCD_RD_CLR	PFout(15)=0     //读数据	PF15

//颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 	         0XFFE0
#define GBLUE		 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 	         0XBC40 //棕色
#define BRRED 		 0XFC07 //棕红色
#define GRAY  		0X8430 //灰色
//颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 	         0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

extern  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void LCD_Init(void);
void LCD_Clear(u16 Color);
void LCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color);
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);
void LCD_DrawPoint_big(u16 x,u16 y,u16 color);
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color);
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 color);
void LCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color);
void LCD_ShowFloatNum(u16 x,u16 y,float num,u8 len,u16 color);
void LCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2);
void Show_MMP(void);
#endif



