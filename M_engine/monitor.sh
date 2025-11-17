path=/dev/serial/by-id/$(ls /dev/serial/by-id/ | grep Teensy)

arduino-cli monitor -p $path -c baudrate=115200
