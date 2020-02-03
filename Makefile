ASM=nasm
CROSS:=i686-linux-gnu
CC=$(CROSS)-gcc-8
CPP=$(CROSS)-g++-8
LD=$(CROSS)-ld
MAKE=make
empty:=
space:=$(empty) $(empty)

SOURCES:=$(foreach i,*.cpp *.c *.s,$(shell find ./ -name $(i)))
# SOURCE:=$(wildcard */)
OBJECTS:=$(foreach i,$(SOURCES),$(i).o)

C_FLAGS:=-c -Wall -m32 -ggdb -fno-stack-protector -I include/ -nostdlib -static -fno-use-linker-plugin -fno-rtti -fno-exceptions -fno-use-cxa-atexit

#-nostdinc -fno-builtin -fno-pic 
#LD_FLAGS = -T script/kernel.ld ./lib/crt1.o ./lib/crti.o ./lib/crtbeginT.o $(OBJECTS) ./lib/crtend.o ./lib/crtn.o -o kernel -L ./lib -lstdc++ -lm --start-group -lgcc -lgcc_eh -lc --end-group -static
LD_FLAGS = -T script/kernel.ld $(OBJECTS) -L ./lib

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

depence:
	@$(CPP) $(C_FLAGS) -M $(SOURCES)

# .PHONY: update
# update:
# 	@DEVICE=`losetup -f` && echo device: $$DEVICE && \
# 	sudo losetup -P $$DEVICE ~/Desktop/floppy.img && \
# 	sudo mount "$$DEVICE"p1 /mnt && sudo cp kernel /mnt/ && sleep 1&& sudo umount /mnt && \
# 	sudo losetup -d $$DEVICE

.PHONY:debug
debug: kernel
	@qemu-system-i386 -S -s -kernel kernel &
	@sleep 1
	@gdb -x script/gdbinit

.PHONY: run
run: kernel
	@qemu-system-i386 -kernel kernel

.PHONY: clean
clean:
	@$(foreach i,$(OBJECTS) ./kernel,echo RM   $(i); rm -rf $(i); )

PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)

ECHO:=
.PHONY: ECHO
ECHO:
	echo $(ECHO)

