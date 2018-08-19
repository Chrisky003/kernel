PROJECT = ../..
WORKING = $(PROJECT)/project/kernel
TOOLS = $(PROJECT)/tools
OBJPATH = $(WORKING)/obj
BUILD = $(WORKING)/build
SOURCEPATH = $(WORKING)/source

ASM = nasm
CC = gcc
CPP = g++
LD = ld
MAKE = make

SOURCES := $(SOURCEPATH)/entry.s $(filter-out $(SOURCEPATH)/entry.s, $(wildcard $(SOURCEPATH)/*.*))
OBJECTS := $(subst $(SOURCEPATH), $(OBJPATH), $(patsubst %.s, %.o ,$(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCES)))))
#$(patsubst %.s, %.o ,$(patsubst %.c, %.o, $(SOURCES)))

#无调试:
#C_FLAGS = -c -Wall -m32 -nostdinc -fno-builtin -fno-stack-protector -I include/
#调试:
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include/
LD_FLAGS = -T $(WORKING)/scripts/kernel.ld -m elf_i386 -nostdlib --oformat=elf32-i386
#无调试:
#ASM_FLAGS = -f elf
#调试:
ASM_FLAGS = -f elf -g -F stabs

.PNONY: default
default: 
	@$(MAKE) build/kernel
	
build/kernel: $(patsubst %.s, %.o ,$(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(SOURCES))))
	@echo LD  $(subst $(WORKING)/,, $(BUILD)/kernel)
	@$(LD) $(LD_FLAGS) $(OBJECTS) -o $(BUILD)/kernel
	
.PHONY: build
build:
	@$(MAKE) build/kernel

%.o: %.cpp
#	@echo 开始编译$<
#	@echo 输出文件为：$(OBJPATH)/$(notdir $@)
	@echo CPP  $(subst $(WORKING)/,, $<)
	@$(CPP) $(C_FLAGS) $< -o $(OBJPATH)/$(notdir $@)

%.o: %.s
#	@echo 开始汇编$<
#	@echo 输出文件为：$(OBJPATH)/$(notdir $@)
	@echo AS  $(subst $(WORKING)/,, $<)
	@$(ASM) $(ASM_FLAGS) $< -o $(OBJPATH)/$(notdir $@)


%.o: %.c
#	@echo 开始编译$<
#	@echo 输出文件为：$(OBJPATH)/$(notdir $@)
	@echo CC  $(subst $(WORKING)/,, $<)
	@$(CC) $(C_FLAGS) $< -o $(OBJPATH)/$(notdir $@)

.PHONY: install
install:
	@$(MAKE) mount
	@sudo cp build/kernel /mnt/boot/kernel
	@sleep 1
	@$(MAKE) umount

.PHONY: mount
mount:
	@sudo mount /dev/sdb4 /mnt

.PHONY: umount
umount:
	@sudo umount /mnt
	
.PHONY: run
run:build/kernel
	@$(MAKE) install
	@sudo qemu-system-i386 -hda /dev/sdb4

.PHONY:debug
debug:build/kernel
	@qemu-system-i386 -S -s -hda /dev/sdb4 &
	@sleep 1
	@gdb -tui -x scripts/gdbinit

.PHONY: clean
clean:
	@echo RM   $(subst $(WORKING)/,, $(OBJPATH)/*.*)
	@rm -rf $(OBJPATH)/*.*
	@rm -rf $(OBJPATH)/*
	@echo RM   $(subst $(WORKING)/,, $(BUILD)/*.*)
	@rm -rf $(BUILD)/*.*
	@rm -rf $(BUILD)/*	
	@echo 清理完成!
