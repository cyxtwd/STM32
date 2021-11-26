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

//-----------------LCD�˿ڶ���----------------
//DATAOUT ���������ĥ��ĥ��ô���÷�
#define DATAOUT(x) GPIOF->ODR=((GPIOF->ODR&0xffffff00)|x)//8λ���ݲ������ bit0-7

#define LCD_BKL_ON  PAout(7)=1		//����LED   PA7
#define	LCD_RST_SET	PFout(11)=1     //��λ		PF11
#define	LCD_CS_SET  PFout(12)=1     //Ƭѡ�˿�  	PF12
#define	LCD_DC_SET	PFout(13)=1     //����/����  PF13
#define	LCD_WR_SET	PFout(14)=1     //д����	    PF14
#define	LCD_RD_SET	PFout(15)=1     //������		PF15

#define LCD_BKL_OFF PAout(7)=0		//����LED   PA7
#define	LCD_RST_CLR	PFout(11)=0     //��λ		PF11			    
#define	LCD_CS_CLR  PFout(12)=0     //Ƭѡ�˿�  PF12
#define	LCD_DC_CLR	PFout(13)=0     //����/���� PF13
#define	LCD_WR_CLR	PFout(14)=0     //д����	PF14
#define	LCD_RD_CLR	PFout(15)=0     //������	PF15

//��ɫ
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
#define BROWN 	         0XBC40 //��ɫ
#define BRRED 		 0XFC07 //�غ�ɫ
#define GRAY  		0X8430 //��ɫ
//��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 	         0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

extern  u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ

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



