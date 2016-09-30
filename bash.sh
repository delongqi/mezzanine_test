#!/bin/sh

chmod +x gpio
chmod +x adc
chmod +x serial

echo "GPIO test!"
./gpio
echo "GPIO finshed!"
echo "SPI ADC test!"
./adc
echo "ADC finshed!"
echo "Serial test!"
./serial
echo "Serial finshed!"
echo "I2C test!"
i2cdetect -r -y 0
echo "I2C finshed!"
