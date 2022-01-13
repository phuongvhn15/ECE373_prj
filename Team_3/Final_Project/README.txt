How to disable spidev0.0 or spidev0.1:
	- Enable SPI interface using command: sudo raspi-config
	- Compile file spidev_disabler by command: dtc spidev_disabler.dts -O dtb >spidev_disabler.dtbo
	- Load dts file by command: sudo dtoverlay -d . spidev_disabler