#ifndef __OLED_HARD_I2C_H
#define __OLED_HARD_I2C_H

#include "main.h"
#include "stdlib.h"	

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_WR_Byte(u8 dat,u8 mode);	// 向OLED写入数据/命令
//void OLED_ClearPoint(u8 x,u8 y);
//void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);			

void OLED_Init(void);		// OLED初始化
void OLED_ColorTurn(u8 i);		// 反显设置: 0正常显示, 1反色显示
void OLED_DisplayTurn(u8 i);	// 屏幕旋转: 0正常, 1旋转180度
void OLED_DisPlay_On(void);		// 开启OLED显示
void OLED_DisPlay_Off(void);	// 关闭OLED显示
void OLED_Refresh(void);			// 更新显存到OLED屏幕
void OLED_Clear(void);				// 清除所有数据并更新显存

void OLED_DrawPoint(u8 x,u8 y,u8 t); 									// 画点: x(0-127), y(0-63), t(1填充,0清空)
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);	// 画线: 起点(x1,y1),终点(x2,y2), mode(1填充,0清空)
void OLED_DrawCircle(u8 x,u8 y,u8 r);									// 画圆: 圆心(x,y),半径r

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);								// 显示单个字符: x,y起点, chr字符, size1字体大小(8/12/16/24), mode(0反色,1正常)	  
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);							// 显示字符串: chr字符串指针, 其他参数同上
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);					// 显示数字: num数字, len数字位数, 其他同上
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);							// 显示中文: num汉字序号, size1字体大小(16/24/32/64)
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);											// 滚动显示: num汉字个数, space间隔(列数), mode显示模式(0反色,1正常)
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);	// 显示图片: x,y起点, sizex,sizey图片尺寸, BMP图片数组

#endif

