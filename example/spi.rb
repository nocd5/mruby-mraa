spi = Mraa::Spi.new(5)
puts "-- SPI ECHO BACK --"
p spi.transfer([1, 2, 3, 0xff, 256])
p spi.transfer_byte(0x0f)

