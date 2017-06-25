SOURCES += $(LIBPATH)/src/console.c \
	   $(LIBPATH)/src/keyboard.c \
	   $(LIBPATH)/src/memset.c \
	   $(LIBPATH)/src/printf.c \
	   $(LIBPATH)/src/serial.c \
	   $(LIBPATH)/src/speaker.c \
	   $(LIBPATH)/src/string.c \
	   $(LIBPATH)/src/timer.c \
	   $(LIBPATH)/src/unistd.c

CFLAGS += -I$(LIBPATH)/include

