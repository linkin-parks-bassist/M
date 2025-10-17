# === Project settings ===
BOARD    = teensy:avr:teensy40
MCU      = TEENSY40
SRC     := $(wildcard src/*.c src/*.cpp)
SIMSRC  := simulator/M_teensy_simulator.cpp $(filter-out src/tm_i2s_dma.cpp src/tm_printf.cpp src/tm_sgtl5000.cpp, $(SRC))
SIMOBJ  := $(patsubst src/%.cpp,simulator/obj/%.o,$(SIMSRC))
HDR     := $(wildcard include/*.h)
SIMHDR  := $(filter-out include/tm_i2s_dma.h src/tm_sgtl5000.h, $(HDR))
INO      = $(strip $(basename $(notdir $(wildcard *.ino))))
HEXFILE  = $(BUILD_DIR)/$(INO).ino.hex
GCC		 = g++
SIMFLAGS = -Iinclude -Isimulator -DTM_SIMULATED -g

# Tools
ARDUINO_CLI    = arduino-cli
TEENSY_LOADER  = teensy-loader-cli -v

BUILD_DIR = build

# === Rules ===

all: $(HEXFILE)

generated: ../config/transformers/*.yaml ../codegen.py
	cd ../ && python codegen.py && cd -

$(HEXFILE): $(INO).ino $(SRC) $(HDR) generated
	cp include/*.h src && $(ARDUINO_CLI) compile \
	    --fqbn $(BOARD) \
	    --build-path $(BUILD_DIR) \
	    --build-property build.extra_flags="-Isrc" ; rm src/*.h

simulator/obj/%.o: src/%.cpp $(SIMHDR)
	$(GCC) $(SIMFLAGS) -c $< -o $@

tm_simulator: generated $(SIMSRC) $(HDR) $(SIMOBJ)
	$(GCC) $(SIMFLAGS) $(SIMOBJ) -lsndfile -o tm_simulator

simulator: tm_simulator

simclean: 
	rm simulator/obj/*

upload: $(HEXFILE)
	$(TEENSY_LOADER) -mmcu=$(MCU) -w $(HEXFILE)

clean:
	rm -rf $(BUILD_DIR)

lshex: all
	@echo $(HEXFILE)

