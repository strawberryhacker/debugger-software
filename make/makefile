# Author: strawberryhacker

project_path = $(shell pwd)/..
build_path   = $(project_path)/build
executable   = $(build_path)/binaries/program

#---------------------------------------------------------------------------------------------------

source += $(project_path)/main.c
source += $(project_path)/startup.c
source += $(project_path)/utilities.c
source += $(project_path)/clock.c
source += $(project_path)/gpio.c
source += $(project_path)/print.c
source += $(project_path)/usb.c

include += $(project_path)/include/utilities.h
include += $(project_path)/include/registers.h
include += $(project_path)/include/gpio.h
include += $(project_path)/include/clock.h
include += $(project_path)/include/print.h
include += $(project_path)/include/usb.h
include += $(project_path)/make/makefile

#---------------------------------------------------------------------------------------------------

compile_flags += -x c
compile_flags += -O3
compile_flags += -g3
compile_flags += -Wall
compile_flags += -std=c11
compile_flags += -ffreestanding
compile_flags += -mcpu=cortex-m0plus
compile_flags += -mthumb
compile_flags += -I$(project_path)/include

linker_flags += -nostartfiles
linker_flags += -mthumb
linker_flags += -mcpu=cortex-m0plus
linker_flags += -T$(project_path)/linker/linker.ld

objects = $(addprefix $(build_path), $(subst $(project_path),, $(patsubst %.c, %.o, $(source)))) 

.PHONY: compile clean
.SECONDARY: $(objects)

#---------------------------------------------------------------------------------------------------

compile: $(executable).elf $(executable).lss $(executable).bin
	@sudo edbg -t samd21 -pv -f $(executable).bin

clean:
	@rm -r -f $(build_path)

%.elf: $(objects)
	@mkdir -p $(dir $@)
	@arm-none-eabi-gcc $(linker_flags) $^ -o $@

%.lss: %.elf
	@mkdir -p $(dir $@)
	@arm-none-eabi-objdump -h -S $< > $@

%.bin: %.elf
	@mkdir -p $(dir $@)
	@arm-none-eabi-objcopy -O binary $< $@

$(build_path)/%.o: $(project_path)/%.c $(include)
	@mkdir -p $(dir $@)
	@arm-none-eabi-gcc $(compile_flags) -c $< -o $@