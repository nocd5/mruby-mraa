ADDR_Si7013 = 0x40
ADDR_Si1145 = 0x60
ADDR_ADXL345 = 0x1d

i2c = Mraa::I2c.new(1)
Mraa.result_print i2c.address(ADDR_Si7013)
Mraa.result_print i2c.write_byte(0xE3)
data, len = i2c.read(2)
puts "data: " + data.to_s
puts "len: " + len.to_s

Mraa.result_print i2c.address(ADDR_ADXL345)
puts "ADXL345 DEVID: " + i2c.read_reg(0).to_s(2)
i2c.write_reg(3, 0x1d)
puts "write/read: " + i2c.read_reg(0x1d).to_s

