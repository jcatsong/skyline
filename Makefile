TARGET = skyline
BUILD_DIR = build


#######################################
# Tools
#######################################
BINPATH = /Users/seanlee/opt/arm-toolchain/bin
PREFIX = arm-none-eabi-
CC = $(BINPATH)/$(PREFIX)gcc
AS = $(BINPATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(BINPATH)/$(PREFIX)objcopy
AR = $(BINPATH)/$(PREFIX)ar
SZ = $(BINPATH)/$(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# CFLAGS
#######################################
INCLUDES = -I./inc \
					 -I./lib/inc \
					 -I./CMSIS/Device/ST/STM32F0xx/Include \
					 -I./CMSIS/Include
VERBOSE =
DEBUG = -g
OPT =
MCU = -mcpu=cortex-m0 -mthumb
CFLAGS = $(MCU) $(DEBUG) $(VERBOSE) $(INCLUDES) -Wall -fdata-sections -ffunction-sections


#######################################
# C Sources
#######################################
SRC = ./src/main.c \
			./src/gpio.c \
			./src/uart.c \
			./src/system.c \
			./src/stats.c \
			./src/stm32f0xx_it.c \
			./src/system_stm32f0xx.c \
			./lib/src/buffer.c \


#######################################
# Assembly Sources
#######################################
STARTUP = ./startup/startup_stm32f030x8.s


#######################################
# Linker
#######################################
LDSCRIPT = ./linker/STM32F030R8Tx_FLASH.ld
LIBS = -lc -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(STARTUP:.s=.o)))
OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))
vpath %.c $(sort $(dir $(SRC)))
vpath %.s $(sort $(dir $(STARTUP)))

#######################################
# Build, flash, and debug targets
#######################################
all: $(BUILD_DIR) $(OBJS) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo "############################################"
	@echo "Done generating all file formats"
	@echo "############################################"
	$(SZ) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(HEX) $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(BIN) $< $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo "############################################"
	@echo "Generating elf files"
	@echo "############################################"

	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: %.c
	@echo "############################################"
	@echo "Generating object files from C source"
	@echo "############################################"

	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile
	@echo "############################################"
	@echo "Generating object files from Assembly source"
	@echo "############################################"

	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)

# debug
print-%:
	@echo $* = $($*)
