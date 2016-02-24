# libssd1306
一个在树莓派上的使用ssd1306芯片的oled显示屏的用户空间驱动

# 安装
本程序依赖以下的库
* wiringPi
demo程序还依赖
* libtftgfx
建议同时配合我github上面的libtftgfx图形库来使用，降低开发成本

# 使用
编译并安装库
```
make
make install
```
如需要编译示例程序，执行``make demo``，然后``./demo``就可以运行示例程序

