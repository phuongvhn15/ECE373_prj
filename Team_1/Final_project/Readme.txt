MCP2515_read là hàm dùng để đọc CAN message.
	- Để đọc CAN message cần phải truyền cho nó một buffer có kích thước là 10.
	- Trong đó: 
			byte[0] : CAN id
			byte[1] : CAN dlc
			byte[2] - byte[10]: 8 byte CAN data
	- CAN data có độ dài mặc định là 8 bát kể CAN dlc có giá trị nào, các byte dư ra sẽ auto set giá trị bằng 0.

MCP2515_write là hàm dùng để ghi CAN message.
	- Để ghi CAN message cần phải truyền cho nó một buffer chứa CAN message kích thước là 10.
	- Trong đó: 
			byte[0] : CAN id
			byte[1] : CAN dlc
			byte[2] - byte[10]: 8 byte CAN data
	- CAN data có độ dài mặc định là 8 bát kể CAN dlc có giá trị nào, các byte dư ra sẽ auto set giá trị bằng 0. 

Các bước để load driver:
	- Enable SPI interface bằng cách sử dụng câu lệnh: sudo raspi-config
	- Compile dts-overlay bằng cách nhập câu lệnh: dtc spidev_disabler.dts -O dtb >spidev_disabler.dtbo
	- Load file dts bằng cách dùng câu lệnh: sudo dtoverlay -d . spidev_disabler