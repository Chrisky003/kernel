MAJOR_VERSION_NUMBER = 0
MINOR_VERSION_NUMBER = 1
VERSION = alpha
MODULE_NAME = kernel
NAME = module-$(MODULE_NAME)-$(MAJOR_VERSION_NUMBER).$(MINOR_VERSION_NUMBER)-$(VERSION)
PROJECT = ..
WORKING = .
SOURCEPATH = $(WORKING)/source
BUILDPATH = $(PROJECT)/build

ASM = nasm
CC = gcc
CPP = g++
LD = ld
MAKE = make
LDSCRIPTS = $(WORKING)/scripts/kernel.ld
#Initial value is empty
TARGETS =

SOURCES = $(SOURCEPATH)/entry.s $(filter-out $(SOURCEPATH)/entry.s, $(wildcard *s *c *cpp))
OBJECTS = $(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SOURCES))))

#无调试:
#C_FLAGS = -c -Wall -m32 -nostdinc -fno-builtin -fno-stack-protector -I include/
#调试:
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include/

LD_FLAGS = $(if $(LDSCRIPTS)!=,-T $(LDSCRIPTS)) -m i386pe -nostdlib

#无调试:
#ASM_FLAGS = -f elf
#调试:
ASM_FLAGS = -f elf -g -F stabs

.PNONY: all
all:
	@$(MAKE) build

.PHONY: build
build:TARGETS=build
build: $(SUBDIRS) $(OBJECTS)
	@echo LD  $(subst $(WORKING)/,, $(BUILDPATH)/$(NAME))
	@$(LD) $(LD_FLAGS) $(OBJECTS) -o $(BUILDPATH)/$(NAME)

%.o: %.cpp FORCE
	@echo CPP  $(subst $(WORKING)/,, $<)
	@$(CPP) $(C_FLAGS) $< -o $@

%.o: %.s FORCE
	@echo AS  $(subst $(WORKING)/,, $<)
	@$(ASM) $(ASM_FLAGS) $< -o $@


%.o: %.c FORCE
	@echo CC  $(subst $(WORKING)/,, $<)
	@$(CC) $(C_FLAGS) $< -o $@

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

.PHONY: clean
clean:TARGETS=clean
clean:$(SUBDIRS)
	@echo RM   $(subst $(WORKING)/,, $(SOURCEPATH)/*.o)
	@rm -rf *.o
	@echo RM   $(NAME)
	@rm -rf $(BUILDPATH)/$(NAME)
	@echo module-$(MODULE_NAME)清理完成!

PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
