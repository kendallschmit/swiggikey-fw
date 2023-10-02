# Things you need:
# - make
# - arm-none-eabi GCC toolchain
# - dfu-util

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
DFU_UTIL = dfu-util

CFLAGS = -march=armv6-m -mtune=cortex-m0 -mfloat-abi=soft -mthumb
CFLAGS += -Os -Wl,--gc-sections
CFLAGS += -std=c11 -Wall -MMD -MP

LDFLAGS = --specs=nosys.specs -T $(linker_script) -nostdlib
LDLIBS =

dfu_util_flashmem = --alt '@Internal Flash  /0x08000000/064*0002Kg' --dfuse-address 0x08000000:0x00020000
dfu_util_optionmem = --alt '@Option Bytes  /0x1FFFF800/01*016 e' --dfuse-address 0x1FFFF800
#dfu_util_args += -v -v -v

linker_script=stm32f072rbt6.ld

bin := fw.bin
elf := fw.elf

src := $(wildcard *.c)
obj := $(src:%.c=%.o)
dep := $(src:%.c=%.d)

flashmem_bin := flashmem.bin

clean_files = $(bin) $(elf) $(obj) $(dep) $(flashmem_bin)

define help_message
               _             _ _                      __
              (_)           (_) |                    / _|
  _____      ___  __ _  __ _ _| | _____ _   _ ______| |___      __
 / __\ \ /\ / / |/ _` |/ _` | | |/ / _ \ | | |______|  _\ \ /\ / /
 \__ \\ V  V /| | (_| | (_| | |   <  __/ |_| |      | |  \ V  V /
 |___/ \_/\_/ |_|\__, |\__, |_|_|\_\___|\__, |      |_|   \_/\_/
                  __/ | __/ |            __/ |
                 |___/ |___/            |___/

MAKE TARGETS

    build      Build firmware (generates $(bin))
    clean      Remove generated files

    dfu-list   List USB DFU devices with the appropriate --alt names
    dfu-read   Read device flash memory to $(flashmem_bin)
    dfu-write  Write $(bin) to device flash memory

endef
.PHONY: help
help:
	$(info $(help_message))


-include $(dep)

# Generate .bin file from .elf
$(bin): $(elf)
	$(OBJCOPY) -O binary $< $@

# Link .o, generate .elf
$(elf): $(obj)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Make targets for user
.PHONY: build
build: $(bin)

.PHONY: clean
clean:
	$(RM) $(clean_files)

.PHONY: dfu-list
dfu-list:
	$(DFU_UTIL) -l

.PHONY: dfu-read
dfu-read:
	rm -f $(flashmem_bin)
	$(DFU_UTIL) $(dfu_util_args) $(dfu_util_flashmem) --upload "$(flashmem_bin)"

.PHONY: dfu-write
dfu-write: $(bin)
	$(DFU_UTIL) $(dfu_util_args) $(dfu_util_flashmem) --download "$(bin)"
