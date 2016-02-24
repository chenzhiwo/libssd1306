LIB_NAME=libssd1306.so
DEMO_NAME=demo
PERFIX=/usr

CC=gcc
CFLAGS=-O0 -Wall
LDFLAGS=-lwiringPi -ltftgfx

.PHONY:clean rebuild exec debug install

all:$(LIB_NAME)

clean:
	@echo "Cleaning workspace.........."
	-rm ./*.o ./$(LIB_NAME) ./$(DEMO_NAME)

rebuild:clean all

exec:all install $(DEMO_NAME)
	./$(DEMO_NAME)

debug:CFLAGS+=-g
debug:rebuild
	gdb ./$(DEMO_NAME)

install:$(LIB_NAME)
	install --mode=0644 libssd1306.h  $(PERFIX)/include/
	install --mode=0644 libssd1306.so $(PERFIX)/lib/

uninstall:
	-rm  $(PERFIX)/include/libssd1306.h
	-rm  $(PERFIX)/lib/libssd1306.so

$(LIB_NAME):libssd1306.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -shared -fPIC

$(DEMO_NAME):demo.o
	$(CC) $^ -o $@ -lssd1306 -ltftgfx
