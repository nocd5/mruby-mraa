gpio = Mraa::Gpio.new(Mraa::INTEL_EDISON_GP13)
gpio.dir(Mraa::Gpio::IN)
gpio.enable_irq(Mraa::Gpio::EDGE_BOTH)

loop {
  if (gpio.irq == true) then
    p "hello mraa!"
    gpio.disable_irq
    break
  end
}

