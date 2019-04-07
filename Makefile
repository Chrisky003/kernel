ASM=nasm
CROSS:=i686-linux-gnu
CC=$(CROSS)-gcc
CPP=$(CROSS)-g++
LD=$(CROSS)-ld
MAKE=make
empty:=
space:=$(empty) $(empty)

SOURCES=$(wildcard source/*.s) $(wildcard source/*.c) $(wildcard source/*.cpp)
# SOURCE:=$(wildcard */)
OBJECTS:=$(foreach i,$(SOURCES),$(i).o)

C_FLAGS:=-c -Wall -m32 -ggdb -fno-stack-protector -I include/ -nostdlib -static -fno-use-linker-plugin

#-nostdinc -fno-builtin -fno-pic 
#LD_FLAGS = -T script/kernel.ld ./lib/crt1.o ./lib/crti.o ./lib/crtbeginT.o $(OBJECTS) ./lib/crtend.o ./lib/crtn.o -o kernel -L ./lib -lstdc++ -lm --start-group -lgcc -lgcc_eh -lc --end-group -static
LD_FLAGS = -T script/kernel.ld $(OBJEECTS) -L ./lib --start-group -lgcc_eh --end-group -static

ASM_FLAGS:=-f elf -g -F dwarf

.PNONY: all
all:
	@$(MAKE) build

.PHONY: build
build: $(OBJECTS)
	@echo LD  kernel
	@$(LD) $(LD_FLAGS) -o kernel

kernel: $(OBJECTS)
	@$(MAKE) build

%.cpp.o: %.cpp
	@echo CPP  $<
	@$(CPP) $(C_FLAGS) $< -o $@

%.s.o: %.s
	@echo AS  $<
	@$(ASM) $(ASM_FLAGS) $< -o $@

#%.o: %.c
#	@echo CC  $<
#	@$(CC) $(C_FLAGS) $< -o $@

DEVICE:=
.PHONY: update
update:DEVICE:=$(shell losetup -f)
update:
	@echo device: $(DEVICE)
	@sudo losetup -P $(DEVICE) ~/Desktop/floppy.img
	@sudo mount $(DEVICE)p1 /mnt
	@sudo cp kernel /mnt/
	@sleep 1
	@sudo umount /mnt
	@sudo losetup -d $(DEVICE)

.PHONY:debug
debug: kernel
	@$(MAKE) update
	@qemu-system-i386 -S -s -hda ~/Desktop/floppy.img &
	@sleep 1
	@gdb -tui -x script/gdbinit

.PHONY: run
run: kernel
	@$(MAKE) update
	@qemu-system-i386 -hda ~/Desktop/floppy.img

.PHONY: clean
clean:
	@echo RM   source/*.o
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
	echo $(ECHO)
