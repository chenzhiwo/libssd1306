#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "libssd1306.h"


int pin_clk = 0, pin_mosi = 0, pin_cs = 0, pin_dc = 0;


//通过x,y坐标来寻址buffer中的字节
#define SSD_BUFFER(x, y) ssd_buffer[((( (y) / 8) * SSD_X_BYTE) + (x) )]

//ssd的显示内容缓冲区
uchar ssd_buffer[SSD_BYTE] = "";

//串行端口使能
void ssd_write_enable(void)
{
	digitalWrite(pin_cs, LOW);
}


//串行端口失能
void ssd_write_disable(void)
{
	digitalWrite(pin_cs, HIGH);
}


//向串行端口写入一字节数据
void ssd_write_byte(uchar data)
{
	int offset = 0;
	ssd_write_enable();

	for(offset = 0; offset < 8; offset++)
	{
		digitalWrite(pin_clk, LOW);
		if((data & 0x80) != 0)
		{
			digitalWrite(pin_mosi, HIGH);
		}else{
			digitalWrite(pin_mosi, LOW);
		}
		digitalWrite(pin_clk, HIGH);
		data = data << 1;
	}
	digitalWrite(pin_clk, LOW);

	ssd_write_disable();
}


//向串行端口写入一字节的命令
void ssd_write_command(uchar command)
{
	digitalWrite(pin_dc, LOW);
	ssd_write_byte(command);
}


//向串行端口写入一字节的图像数据
void ssd_write_data(uchar data)
{
	digitalWrite(pin_dc, HIGH);
	ssd_write_byte(data);
}

//初始化显示屏
void ssd_init( int clk, int mosi, int cs, int dc)
{
	wiringPiSetup();
	//把传入的引脚参数复制给全局变量，以方便其他函数使用
	pin_clk = clk;
	pin_mosi = mosi;
	pin_cs = cs;
	pin_dc = dc;

	pinMode(pin_clk , OUTPUT);
	pinMode(pin_mosi , OUTPUT);
	pinMode(pin_cs , OUTPUT);
	pinMode(pin_dc , OUTPUT);

	//关闭显示
//	ssd_write_command(0xae);
	//设置列地址低4位为0
	ssd_write_command(0x00);
	//设置列地址高4位为0
	ssd_write_command(0x10);
	//设置起始行地址为0
	ssd_write_command(0x40);
	//设置对比度为0xcf
	ssd_write_command(0x81);
	ssd_write_command(0xcf);
	//设置列地址重映射
	ssd_write_command(0xa0);
	//设置为正常显示模式
	ssd_write_command(0xa6);
	//设置驱动路数为168列
	ssd_write_command(0xa8);
	//64行
	ssd_write_command(0x3f);
	ssd_write_command(0xd3);
	ssd_write_command(0x00);
	ssd_write_command(0xd5);
	ssd_write_command(0x80);
	ssd_write_command(0xd9);
	ssd_write_command(0xf1);
	ssd_write_command(0xda);
	ssd_write_command(0x12);
	ssd_write_command(0xdb);
	ssd_write_command(0x40);
	ssd_write_command(0x8d);
	ssd_write_command(0x14);
	ssd_write_command(0xaf);

	//设置回页寻址模式
	ssd_write_command(0x20);
	ssd_write_command(0x02);

	//segment重映射模式，为了适应屏幕方向
	ssd_write_command(0xa1);
	//common重映射模式
	ssd_write_command(0xc8);

	ssd_write_disable();
}

void ssd_clean(void)
{
	int i = 0;

	//设置水平寻址模式
	ssd_write_command(0x20);
	ssd_write_command(0x01);

	//设置边界
	ssd_write_command(0x21);
	ssd_write_command(0);
	ssd_write_command(127);

	ssd_write_command(0x22);
	ssd_write_command(0);
	ssd_write_command(7);

	for(i = 0; i < (128 * 8); i++)
	{
		ssd_write_data(0x00);
	}

	//设置回页寻址模式
	ssd_write_command(0x20);
	ssd_write_command(0x02);

	//segment重映射模式，为了适应屏幕方向
	ssd_write_command(0xa1);
	//common重映射模式
	ssd_write_command(0xc8);

}

//设置页指针和列指针
void ssd_set_column_page(uchar column, unsigned page)
{
	ssd_write_command(0x00 | ( 0x0f & column) );
	ssd_write_command(0x10 | (( 0xf0 & column) >> 4) );
	ssd_write_command(0xB0 | page );
}

//设置页寻址模式下的xy坐标设置页指针和列指针的位置
void ssd_set_xy(uchar x, unsigned y)
{
	ssd_set_column_page(x, (y / 8));
}

//把缓冲中的内容刷新到显示屏上
void ssd_buffer_flush(void)
{
	unsigned column = 0, page = 0;
	for(page = 0; page < SSD_PAGE; page++)
	{
		ssd_set_column_page(0, page);
		for(column = 0; column < SSD_COLUMN; column++)
		{
			ssd_write_data(ssd_buffer[(page * SSD_X_BYTE) + column]);
		}
	}
}

//把缓冲区清空，但是不清空RAM
void ssd_buffer_clear(void)
{
	int i = 0;
	for(i = 0; i < SSD_BYTE; i++)
	{
		ssd_buffer[i] = 0x00;
	}

}

void ssd_buffer_draw_pixel(int x, int y, uchar color)
{
	if(x < 0 || x >= SSD_X || y < 0 || y >= SSD_Y)
	{   
		puts("X/Y out of range.");
		return;
	}   

	if(color == COLOR_NONE)
	{   
		SSD_BUFFER(x, y) = SSD_BUFFER(x, y) & ~(0x01 << (y % 8));
	}   
	else if(color == COLOR_ON)
	{   
		SSD_BUFFER(x,y) = SSD_BUFFER(x,y) | (0x01 << (y % 8));
	}
	else if(color == COLOR_DEFAULT)
	{   
	}   
}

//在屏幕上的任意位置绘制一个bitmap
void ssd_buffer_draw_bitmap(int x, int y, int w, int h, uchar bitmap[], uchar color_fg, uchar color_bg)
{
	//记录bitmap的内部坐标
	int bx = 0, by = 0;       
	if(x < 0 || x >= SSD_X || y < 0 || y >= SSD_Y)
	{  
		puts("X/Y out of range.");     
		return;
	}  
	if((x + w) > SSD_X || (y + h) > SSD_Y) 
	{  
		puts("H/W out of range.");     
		return;
	}  

	for(by = 0; by < h; by++) 
	{  
		for(bx = 0; bx < w; bx++)      
		{
			if((bitmap[(by / 8) * w + bx] & (0x01 << (by % 8))) == 0)
			{
				ssd_buffer_draw_pixel(x + bx, y + by, color_bg);
			} else {
				ssd_buffer_draw_pixel(x + bx, y + by, color_fg);
			}

		}
	}                         

}

void ssd_buffer_draw_bitmapbin(int x, int y, int w, int h, uchar bitmap[], uchar color_fg, uchar color_bg)
{
	int bx = 0, by = 0;
	;
	if(x < 0 || x >= SSD_X || y < 0 || y >= SSD_Y)
	{
		puts("X/Y out of range.");
		return;
	}
	if((x + w) > SSD_X || (y + h) > SSD_Y)
	{
		puts("H/W out of range.");
		return;
	}

	for(bx = 0; bx < w; bx++)
	{
		for(by = 0; by < h; by++)
		{
			if((bitmap[by * ((w / 8)) + (bx / 8)] & (0x80 >> (bx % 8))) == 0)
			{
				ssd_buffer_draw_pixel(x + bx, y + by, color_bg);
			}
			else
			{
				ssd_buffer_draw_pixel(x + bx, y + by, color_fg);
			}
		}
	}

}


//int main(int argc, char * args[])
//{
//	ssd_init();
//	ssd_clean();
//	ssd_buffer_clear();
//	char bitmap[] = {0x3e, 0x41, 0x49, 0x49, 0x7a};
//
//	int i = 0;
//
//	for(i = 0; i < SSD_X; i++)
//	{
//		ssd_buffer_clear();
//		ssd_buffer_draw_bitmap(i,0,5,8,bitmap,COLOR_ON, COLOR_NONE);
//		ssd_buffer_flush();
//		usleep(100000);
//	}
//
//
//
//
//	return EXIT_SUCCESS;
//}
