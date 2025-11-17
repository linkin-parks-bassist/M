# === Project settings ===
BOARD	= teensy:avr:teensy40
MCU	  = TEENSY40

GCC	  = gcc
GPP	  = g++
SIMFLAGS = -Iinclude -I../shared -Isimulator -DM_SIMULATED -DM_ENGINE -g -fpermissive

CMSIS_OBJ = ../teensy4/teensy-compile/11.3.1/arm/arm-none-eabi/lib/libarm_cortexM7lfsp_math.a

# Tools
ARDUINO_CLI	= arduino-cli
TEENSY_LOADER  = teensy-loader-cli -v

BUILD_DIR = build

# === GCC (bare-metal) build: Teensy 4.0 with system Arm GCC ===

.PHONY: gcc gcc_flash gcc_clean all flash clean fullclean simulator simclean

# Toolchain (system packages)
ARM_GCC ?= /usr/bin
CC	  := $(ARM_GCC)/arm-none-eabi-gcc
CXX	 := $(ARM_GCC)/arm-none-eabi-g++
OBJCOPY := $(ARM_GCC)/arm-none-eabi-objcopy

# Teensy 4 core and linker script
CORE_PATH	 := ../teensy4/hardware/avr/1.59.0/cores/teensy4
LIBS_PATH	 := ../teensy4/hardware/avr/1.59.0/libraries
LD_SCRIPT	 := $(CORE_PATH)/imxrt1062.ld

# === Sources ===
CORE_SRC_C	:= $(wildcard $(CORE_PATH)/*.c)
CORE_SRC_CPP  := $(wildcard $(CORE_PATH)/*.cpp $(CORE_PATH)/*/*.cpp)

# Exclude Arduino entrypoint and Audio library
CORE_SRC_CPP  := $(filter-out \
	$(CORE_PATH)/main.cpp \
	$(CORE_PATH)/Blink.cc \
	$(CORE_PATH)/AudioStream.cpp \
	$(CORE_PATH)/usb_audio.cpp \
	$(CORE_PATH)/usb_midi.cpp, \
	$(CORE_SRC_CPP))

PRJ_SRC_C	  := $(wildcard src/*.c src/utility/*.c)
PRJ_SRC_CPP	:= $(wildcard src/*.cpp src/utility/*.cpp)
PRJ_SRC_S	  := $(wildcard src/**/*.S src/*.S)
PRJ_SHARED_SRC := $(wildcard ../shared/*.c)

# === Objects ===
OBJ_CORE_C	:= $(patsubst $(CORE_PATH)/%.c,$(BUILD_DIR)/core/%.o,$(CORE_SRC_C))
OBJ_CORE_CPP  := $(patsubst $(CORE_PATH)/%.cpp,$(BUILD_DIR)/core/%.o,$(CORE_SRC_CPP)) \
				 $(patsubst $(LIBS_PATH)/Wire/%.cpp,$(BUILD_DIR)/wire/%.o,$(wildcard $(LIBS_PATH)/Wire/*.cpp)) \
				 $(patsubst $(LIBS_PATH)/SPI/%.cpp,$(BUILD_DIR)/spi/%.o,$(wildcard $(LIBS_PATH)/SPI/*.cpp))

OBJ_PRJ_C	 := $(patsubst src/%.c,$(BUILD_DIR)/obj/%.o,$(PRJ_SRC_C)) \
				 $(patsubst ../shared/%.c,$(BUILD_DIR)/obj/%.o,$(PRJ_SHARED_SRC))
OBJ_PRJ_CPP   := $(patsubst src/%.cpp,$(BUILD_DIR)/obj/%.o,$(PRJ_SRC_CPP))
OBJ_S		 := $(patsubst src/%.S,$(BUILD_DIR)/obj/%.o,$(PRJ_SRC_S))

OBJS		  := $(OBJ_CORE_C) $(OBJ_CORE_CPP) $(OBJ_PRJ_C) $(OBJ_PRJ_CPP) $(OBJ_S)

INCLUDE_FLAGS := -Iinclude -I../shared -Isrc -I$(CORE_PATH) -I$(CORE_PATH)/debug -I$(LIBS_PATH) -I$(LIBS_PATH)/Wire

# === Flags ===
COMMON_CPU := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard
CFLAGS_GCC := $(COMMON_CPU) -Ofast -ffunction-sections -fdata-sections \
			  -DF_CPU=600000000 -D__IMXRT1062__ -DARDUINO_TEENSY40 \
			  -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DM_ENGINE \
			  $(INCLUDE_FLAGS)

CXXFLAGS_BASE := $(CFLAGS_GCC) -D__ASSEMBLER__=0 -DARDUINO=10813 -DTEENSYDUINO=159 \
				 -fno-rtti -fno-exceptions -include type_traits

CXXFLAGS_GCC   := $(CXXFLAGS_BASE) -std=gnu++17
CXXFLAGS_GCC14 := $(CXXFLAGS_BASE) -std=gnu++14 -fpermissive -w

# === Linker ===
LDFLAGS_GCC := -T$(LD_SCRIPT) -Wl,--gc-sections \
			   -Wl,--start-group -lc -lm -lstdc++ -lgcc -Wl,--end-group $(CMSIS_OBJ)

# === Targets ===
all: generated $(BUILD_DIR)/m_engine.hex

generated:
	cd ../ && python codegen.py && cd -

flash: $(BUILD_DIR)/m_engine.hex
	teensy-loader-cli -v -mmcu=$(MCU) -w $(BUILD_DIR)/m_engine.hex

clean:
	rm -rf $(BUILD_DIR)/obj

fullclean:
	rm -rf $(BUILD_DIR)

# === Link + convert ===
$(BUILD_DIR)/m_engine.elf: $(OBJS) | $(BUILD_DIR)
	$(CXX) $(COMMON_CPU) $(OBJS) $(LDFLAGS_GCC) -o $@

$(BUILD_DIR)/m_engine.hex: $(BUILD_DIR)/m_engine.elf
	$(OBJCOPY) -O ihex $< $@

# === Compile rules ===
$(BUILD_DIR)/core/%.o: $(CORE_PATH)/%.c | $(BUILD_DIR)/core
	$(CC) $(CFLAGS_GCC) -c $< -o $@

$(BUILD_DIR)/core/%.o: $(CORE_PATH)/%.cpp | $(BUILD_DIR)/core
	$(CXX) $(CXXFLAGS_GCC) -c $< -o $@

$(BUILD_DIR)/obj/%.o: src/%.c | $(BUILD_DIR)/obj $(BUILD_DIR)/obj/utility
	$(CC) $(CFLAGS_GCC) -c $< -o $@

$(BUILD_DIR)/obj/%.o: src/%.S | $(BUILD_DIR)/obj
	$(CC) $(COMMON_CPU) $(INCLUDE_FLAGS) -x assembler-with-cpp -c $< -o $@

$(BUILD_DIR)/obj/%.o: src/%.cpp | $(BUILD_DIR)/obj
	$(CXX) $(CXXFLAGS_GCC) -c $< -o $@

$(BUILD_DIR)/obj/%.o: ../shared/%.c | $(BUILD_DIR)/obj
	$(CC) $(CFLAGS_GCC) -c $< -o $@

$(BUILD_DIR)/wire/%.o: $(LIBS_PATH)/Wire/%.cpp | $(BUILD_DIR)/wire
	$(CXX) $(CXXFLAGS_GCC14) -c $< -o $@

$(BUILD_DIR)/spi/%.o: $(LIBS_PATH)/SPI/%.cpp | $(BUILD_DIR)/spi
	$(CXX) $(CXXFLAGS_GCC) -c $< -o $@

# === Dirs ===
$(BUILD_DIR) \
$(BUILD_DIR)/core \
$(BUILD_DIR)/obj \
$(BUILD_DIR)/wire \
$(BUILD_DIR)/obj/utility \
$(BUILD_DIR)/spi:
	mkdir -p $@

# === Simulator build ===

SIM_SHARED_SRC := ../shared/m_alloc.c \
				  ../shared/m_comms.c \
				  ../shared/m_error_codes.c \
				  ../shared/m_transformer_enum.c

SIM_SRC := simulator/m_eng_sim.c \
		   $(filter-out \
			 src/m_eng.cpp \
			 src/m_eng_i2s_dma.cpp \
			 src/m_eng_sgtl5000.cpp \
			 src/m_alloc.c \
			 src/m_comms.c \
			 src/m_error_codes.c \
			 src/m_transformer_enum.c, \
			 $(wildcard src/*.c src/*.cpp)) \
		   $(SIM_SHARED_SRC)

SIM_OBJ := $(patsubst src/%.c,simulator/obj/%.o,$(filter src/%.c,$(SIM_SRC))) \
		   $(patsubst src/%.cpp,simulator/obj/%.o,$(filter src/%.cpp,$(SIM_SRC))) \
		   $(patsubst ../shared/%.c,simulator/obj/%.o,$(filter ../shared/%.c,$(SIM_SRC))) \
		   simulator/obj/m_eng_sim.o

m_simulator: $(SIM_OBJ)
	$(GCC) $(SIMFLAGS) $(SIM_OBJ) -lsndfile -lm -o $@

simulator: generated m_simulator

# --- simulator object build rules ---
simulator/obj/%.o : simulator/%.c | simulator/obj
	$(GCC) $(SIMFLAGS) -c $< -o $@

simulator/obj/%.o : src/%.c | simulator/obj
	$(GCC) $(SIMFLAGS) -c $< -o $@

simulator/obj/%.o : src/%.cpp | simulator/obj
	$(GPP) $(SIMFLAGS) -c $< -o $@

simulator/obj/%.o : ../shared/%.c | simulator/obj
	$(GCC) $(SIMFLAGS) -c $< -o $@

simulator/obj:
	mkdir -p simulator/obj

simclean:
	rm -rf simulator/obj
