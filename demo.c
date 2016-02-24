#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libssd1306.h>
#include <libtftgfx.h>

//84x48的bitmap
uchar bitmap[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x30, 0x18, 0x1C,
	0x0C, 0x0C, 0x06, 0x06, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
	0x07, 0x07, 0x0E, 0x06, 0x1C, 0x1C, 0x38, 0x70, 0x70, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0x3C, 0xCE, 0x67, 0x33, 0x18, 0x08,
	0x08, 0xC8, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
	0x70, 0x38, 0x18, 0x18, 0x08, 0x08, 0x08, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x01, 0x07,
	0x0F, 0x3C, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0x0C, 0x7F,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x61, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7F, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x63,
	0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF,
	0xF0, 0x00, 0x00, 0x00, 0x08, 0x08, 0xFC, 0x8C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x3C, 0x70, 0xE0, 0x80, 0x00, 0x07, 0x0C, 0x38, 0x60, 0xC0,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0,
	0xF0, 0xE0, 0xC0, 0x80, 0xC0, 0x30, 0x18, 0x0F, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x3C, 0x1F, 0x07,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06,
	0x0E, 0x1C, 0x18, 0x38, 0x31, 0x73, 0x62, 0x66, 0x64, 0xC7, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF,
	0xC7, 0xC7, 0xC7, 0x67, 0x63, 0x63, 0x71, 0x30, 0x38, 0x18, 0x1C, 0x0C, 0x06, 0x03, 0x03, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
};

//16x16的直观绘制方式的bitmap
uchar bitmap_bin[] = {
	0B00000000, 0B11000000,
	0B00000001, 0B11000000,
	0B00000001, 0B11000000,
	0B00000011, 0B11100000,
	0B11110011, 0B11100000,
	0B11111110, 0B11111000,
	0B01111110, 0B11111111,
	0B00110011, 0B10011111,
	0B00011111, 0B11111100,
	0B00001101, 0B01110000,
	0B00011011, 0B10100000,
	0B00111111, 0B11100000,
	0B00111111, 0B11110000,
	0B01111100, 0B11110000,
	0B01110000, 0B01110000,
	0B00000000, 0B00110000
};

int main(int argc, char * argv[])
{
	/*-----------------------------------------------------------------------------
	 *  初始化ssd1306库，引脚clk, mosi, cs, d/c分别为wiringPi引脚定义的
	 *  22,23,24,25
	 *-----------------------------------------------------------------------------*/
	ssd_init(22, 23, 24, 25);
	ssd_clean();
	/*-----------------------------------------------------------------------------
	 *  把ssd1306库包装好的底层函数作为参数来初始化libtftgfx库，初始化以后就可以使用
	 *  libtftgfx库提供的一系列函数来绘图了
	 *-----------------------------------------------------------------------------*/
	gfxInitStruct gfx = {};
	gfx.HWFlushFunc = ssd_buffer_flush;
	gfx.HWClearFunc = ssd_buffer_clear;
	gfx.HWDrawPixelFunc = ssd_buffer_draw_pixel;
	gfx.HWDrawBitMapFunc = ssd_buffer_draw_bitmap;
	gfx.HWDrawBitMapBinFunc = ssd_buffer_draw_bitmapbin;
	gfxInit(gfx);

	//清屏
	gfxClear();
	gfxFlush();

	//打印文字
	gfxClear();
	gfxPrintASCII5x8(0,0,"libssd1306", COLOR_ON, COLOR_DEFAULT);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawBitMap(1,1,84,48,bitmap, COLOR_ON, COLOR_DEFAULT);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawBitMapBin(5,5,16,16,bitmap_bin, COLOR_ON, COLOR_DEFAULT);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawLine(5,5,40,40,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawCircle(30,30,20,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawFillCircle(30,30,20,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawRect(20,20,40,40,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawFillRect(20,20,40,40,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawRoundRect(20,20,40,40,8,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawFillRoundRect(20,20,40,40,8,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawTriangle(10,10,80,10,40,30,COLOR_ON);
	gfxFlush();
	sleep(1);

	gfxClear();
	gfxDrawFillTriangle(10,10,80,10,40,30,COLOR_ON);
	gfxFlush();
	sleep(1);

	return EXIT_SUCCESS;
}
