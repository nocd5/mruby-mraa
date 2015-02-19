gpio = Mraa::Gpio.new(Mraa::INTEL_EDISON_GP13)
led = gpio.read  == 0 ? 1 : 0
gpio.dir(Mraa::Gpio::OUT)
gpio.write(led)

