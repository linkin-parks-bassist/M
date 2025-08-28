#!/bin/bash

make && make upload && arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200
