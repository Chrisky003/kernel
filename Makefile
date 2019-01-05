ASM=nasm
CC=gcc
CPP=g++
LD=ld
MAKE=make
LDSCRIPTS=script/kernel.ld

SOURCES=$(wildcard source/*.s) $(wildcard source/*.c) $(wildcard source/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SOURCES))))

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -fno-pic -I include/

LD_FLAGS = $(if $(LDSCRIPTS)!=,-T $(LDSCRIPTS)) -m elf_i386 -nostdlib

ASM_FLAGS = -f elf -g -F stabs

.PNONY: all
all:
	@$(MAKE) build

.PHONY: build
build: $(OBJECTS)
	@echo LD  kernel
	@$(LD) $(LD_FLAGS) $(OBJECTS) -o kernel

%.o: %.cpp
	@echo CPP  $<
	@$(CPP) $(C_FLAGS) $< -o $@

%.o: %.s
	@echo AS  $<
	@$(ASM) $(ASM_FLAGS) $< -o $@

%.o: %.c
	@echo CC  $<
	@$(CC) $(C_FLAGS) $< -o $@

DEVICE:=
.PHONY:debug
debug:DEVICE=$(shell sudo losetup -Pf --show ~/Desktop/floppy.img)
debug:build
	@sudo mount $(DEVICE)p1 /mnt
	@sudo cp kernel /mnt/
	@sudo umount /mnt
	@sudo losetup -d $(DEVICE)
	@$(MAKE) debug_run

.PHONY: debug_run
debug_run:
	@qemu-system-i386 -S -s -hda ~/Desktop/floppy.img &
	@sleep 1
	@gdb -tui -x script/gdbinit

.PHONY: clean
clean:
	@echo RM   *.o
	@rm -rf source/*.o
	@echo RM   kernel
	@rm -rf kernel
	@echo 清理完成!

PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)

ECHO:=
.PHONY: ECHO
ECHO:
	@echo $(ECHO)