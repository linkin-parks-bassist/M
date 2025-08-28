#!/bin/bash

echo "Press the button"
teensy-loader-cli --mcu=TEENSY40 -w -b && arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200
