SOURCES += kernel/kmain.c

LIBPATH=lib
include $(LIBPATH)/lib.mk

CC = gcc
AS = nasm
LD = ld
OBJCOPY = objcopy
CP = cp
DEL = rm

CFLAGS  += -nostdinc -nostdlib -m32 -std=gnu99 -ffreestanding -fno-builtin \
	   -Os -Wall -Wextra
ASFLAGS += -f elf32
LDFLAGS += -nostdlib

OBJECTS  = $(SOURCES:.c=.o)

all: kernel.elf

kernel.elf: kernel.o
	$(OBJCOPY) -I elf32-i386 $^ $@

kernel.o: boot/loader.o $(OBJECTS)
	$(LD) $(LDFLAGS) -T ld/linker.ld -o $@ $^

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $(CCFLAGS) $<

clean:
	$(DEL) -f **/*.elf *.o **/*.o **/**/*.o iso/boot/*.elf *.img *.iso *.elf

run: kernel.elf
	#qemu-system-i386 -kernel $< -monitor stdio
	qemu-system-i386 -soundhw pcspk -serial stdio -kernel $<
