# Compiling, Linking and Uploading Firmware for STM32F4xx Microcontrollers

# Toolchain definitions
CC					:= arm-none-eabi-gcc
OBJCOPY			:= arm-none-eabi-objcopy
SIZE				:= arm-none-eabi-size
RM					:= rm -f
FILE				:= file

OUTPUT_DIR		:= bin

# Microcontroller-specific definitions
DEVICE_FAMILY	:= STM32F4xx
DEVICE_MODEL	:= STM32F446xx
DEVICE_VARIANT	:= STM32F446RETx

# Compiler and linker flags
CORTEX_FLAGS	:= -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard
COMMON_FLAGS	:= -g3 -O0 -Wall -ffunction-sections -fdata-sections
AS_FLAGS			:= -x assembler-with-cpp

# Include paths
MAIN_INC			:= src
CMSIS_INC		:= lib/CMSIS/Include 
CMSIS_DEV_INC	:= lib/CMSIS/Device/ST/STM32F4xx/Include
HAL_INC			:= lib/STM32F4xx_HAL_Driver/Inc
RTOS_INC			:= lib/FreeRTOS/include 
RTOS_GCC_INC	:= lib/FreeRTOS/portable/GCC/ARM_CM4F

# Source files
MAIN_SRC			:= $(wildcard src/*.c)
HAL_SRC			:= $(wildcard lib/STM32F4xx_HAL_Driver/Src/*.c)
SYSTEM_SRC		:= lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
RTOS_SRC			:= $(wildcard lib/FreeRTOS/*.c) 
RTOS_GCC_SRC	:= $(wildcard lib/FreeRTOS/portable/GCC/ARM_CM4F/*.c) 
RTOS_MEM_SRC	:= $(wildcard lib/FreeRTOS/portable/MemMang/*.c) 

# Startup file and linker script 
STARTUP_CODE	:= lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f446xx.S
LINKER_SCRIPT	:= lib/STM32F446RETX_FLASH.ld

# Sorthand and build definititions
DEFINES			:= -D$(DEVICE_FAMILY) -D$(DEVICE_MODEL) -D$(DEVICE_VARIANT) \
						-DUSE_HAL_DRIVER

SOURCES			:= $(MAIN_SRC) $(HAL_SRC) $(SYSTEM_SRC) $(RTOS_SRC) $(RTOS_GCC_SRC) \
						$(RTOS_MEM_SRC)
OBJECTS			:= $(notdir $(patsubst %.c,%.o,$(SOURCES))) startup_stm32f446xx.o
INCLUDES			:= -I$(MAIN_INC) -I$(CMSIS_DEV_INC) -I$(CMSIS_INC) -I$(HAL_INC) \
						-I$(RTOS_INC) -I$(RTOS_GCC_INC)

CFLAGS			:= $(CORTEX_FLAGS) $(COMMON_FLAGS) $(DEFINES) $(INCLUDES)
AFLAGS			:= $(CORTEX_FLAGS) $(AS_FLAGS) $(DEFINES) $(INCLUDES)
LDFLAGS			:= $(CORTEX_FLAGS) -T $(LINKER_SCRIPT) \
						-Wl,--gc-sections,--relax --specs=nano.specs --specs=nosys.specs \
				   	-Wl,--start-group -lc -lm -Wl,--end-group

# Output definitions
FIRMWARE_ELF	:= $(OUTPUT_DIR)/firmware.elf
FIRMWARE_BIN	:= $(OUTPUT_DIR)/firmware.bin

.PHONY: all

all:
	@echo "Compiling the source files..."
	@$(CC) $(AFLAGS) -c $(STARTUP_CODE)
	@$(CC) $(CFLAGS) -c $(SOURCES)

	@echo "\nLinking the object files..."
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $(FIRMWARE_ELF)
	@$(OBJCOPY) -O binary $(FIRMWARE_ELF) $(FIRMWARE_BIN)
	@$(RM) $(OBJECTS) 

	@echo "\nThe firmware section sizes:"
	@$(SIZE) $(FIRMWARE_ELF)

	@echo "\nThe firmware file format:"
	@$(FILE) $(FIRMWARE_ELF)
