# === Project settings ===
BOARD    = teensy:avr:teensy40
MCU      = TEENSY40
SRC     := $(wildcard src/*.c src/*.cpp)
HDR     := $(wildcard src/*.h)
INO      = $(strip $(basename $(notdir $(wildcard *.ino))))
HEXFILE  = $(BUILD_DIR)/$(INO).ino.hex

# Tools
ARDUINO_CLI    = arduino-cli
TEENSY_LOADER  = teensy-loader-cli -v

BUILD_DIR = build

# === Rules ===

all: $(HEXFILE)

$(HEXFILE): $(INO).ino $(SRC) $(HDR)
	$(ARDUINO_CLI) compile \
	    --fqbn $(BOARD) \
	    --build-path $(BUILD_DIR) \
	    --build-property build.extra_flags="-Isrc -Iaudio" \
	    .


upload: $(HEXFILE)
	$(TEENSY_LOADER) -mmcu=$(MCU) -w $(HEXFILE)

clean:
	rm -rf $(BUILD_DIR)

lshex: all
	@echo $(HEXFILE)

