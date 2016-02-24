#ifndef _SSD1306_H_
#define _SSD1306_H_

#define COLOR_NONE		0
#define COLOR_ON		1
#define COLOR_DEFAULT	2

#define SSD_X		128
#define SSD_Y		64
#define SSD_X_BYTE	SSD_X
#define SSD_Y_BYTE	(SSD_Y / 8)
#define SSD_BYTE	(SSD_X_BYTE * SSD_Y_BYTE)
#define SSD_COLUMN	SSD_X
#define SSD_PAGE	(SSD_Y / 8)

typedef unsigned char uchar;

void ssd_write_enable(void);
void ssd_write_disable(void);
void ssd_write_byte(uchar data);
void ssd_write_command(uchar command);
void ssd_write_data(uchar data);
void ssd_init( int clk, int mosi, int cs, int dc);
void ssd_clean(void);
void ssd_set_column_page(uchar column, unsigned page);
void ssd_set_xy(uchar x, unsigned y);
void ssd_buffer_flush(void);
void ssd_buffer_clear(void);
void ssd_buffer_draw_pixel(int x, int y, uchar color);
void ssd_buffer_draw_bitmap(int x, int y, int w, int h, uchar bitmap[], uchar color_fg, uchar color_bg);
void ssd_buffer_draw_bitmapbin(int x, int y, int w, int h, uchar bitmap[], uchar color_fg, uchar color_bg);


#endif

