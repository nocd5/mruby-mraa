# mruby-mraa
mrbgem for Mraa

```ruby
gpio_led = 48 # GPIO port number of LED
gpio = Mraa::Gpio.new(gpio_led)
gpio.dir(Mraa::Gpio::OUT)
gpio.write(1)
```
