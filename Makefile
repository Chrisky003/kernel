ASM=nasm
CC=gcc
CPP=g++
LD=ld
MAKE=make
LDSCRIPTS=/scripts/kernel.ld

SOURCES=$(wildcard *.s *.c *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SOURCES))))

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include/

LD_FLAGS = $(if $(LDSCRIPTS)!=,-T $(LDSCRIPTS)) -m i386pe -nostdlib

ASM_FLAGS = -f elf -g -F stabs

.PNONY: all
all:
	@$(MAKE) build

.PHONY: build
build: $(OBJECTS)
	@echo LD  $(subst $(WORKING)/,, $(BUILDPATH)/$(NAME))
	@$(LD) $(LD_FLAGS) $(OBJECTS) -o kernel

%.o: %.cpp
	@echo CPP  $<
	@$(CPP) $(C_FLAGS) $< -o obj/$@

%.o: %.s
	@echo AS  $<
	@$(ASM) $(ASM_FLAGS) $< -o obj/$@

%.o: %.c
	@echo CC  $<
	@$(CC) $(C_FLAGS) $< -o obj/$@

# .PHONY: copy
# copy:
# 	@$(MAKE) mount
# 	@sudo cp $(BUILDPATH)/$(NAME) /mnt/boot/kernel
# 	@sleep 1
# 	@$(MAKE) umount

# .PHONY: mount
# mount:
# 	@sudo mount /dev/sdb1 /mnt

# .PHONY: umount
# umount:
# 	@sudo umount /mnt

# .PHONY: run
# run: build/kernel
# 	@$(MAKE) copy
# 	@sudo qemu-system-i386 -hda /dev/sdb

# .PHONY:debug
# debug:build/kernel
# 	@qemu-system-i386 -S -s -hda /dev/sdb &
# 	@sleep 1
# 	@gdb -tui -x scripts/gdbinit

obj:
	mkdir obj

.PHONY: clean
clean:
	@echo RM   obj/*
	@rm -rf obj/
	@echo RM   kernel
	@rm -rf kernel
	@echo 清理完成!

PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)