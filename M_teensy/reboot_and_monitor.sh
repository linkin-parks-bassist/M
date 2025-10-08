#!/bin/bash

echo "Press the button"
teensy-loader-cli --mcu=TEENSY40 -w -s -b && ./monitor.sh
