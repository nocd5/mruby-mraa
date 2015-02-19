pwm = Mraa::Pwm.new Mraa::INTEL_EDISON_GP13
pwm.period 100
pwm.pulsewidth_ms 10
pwm.enable true
loop { }

