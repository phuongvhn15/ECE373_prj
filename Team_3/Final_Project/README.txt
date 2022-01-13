Các bước để disable spidev0.0 hoawcj spidev0.1:
	- Enable SPI interface bằng cách sử dụng câu lệnh: sudo raspi-config
	- Compile file spidev_disabler bằng cách nhập câu lệnh: dtc spidev_disabler.dts -O dtb >spidev_disabler.dtbo
	- Load file dts bằng cách dùng câu lệnh: sudo dtoverlay -d . spidev_disabler