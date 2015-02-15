#include <mruby.h>
#include <mruby/class.h>
#include <mraa.h>

// COMMON
extern mrb_value mrb_mraa_pin_mode_test(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_adc_raw_bits(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_adc_supported_bits(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_set_log_level(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_get_platform_name(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_set_priority(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_version(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_result_print(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_get_platform_type(mrb_state *mrb, mrb_value self);

// PWM
extern mrb_value mrb_mraa_pwm_init(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_write(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_read(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_period(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_period_ms(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_period_us(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_pulsewidth(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_pulsewidth_ms(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_pulsewidth_us(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_enable(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_owner(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_config_ms(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_pwm_config_percent(mrb_state *mrb, mrb_value self);

// AIO
extern mrb_value mrb_mraa_aio_init(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_aio_read(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_aio_read_float(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_aio_set_bit(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_aio_get_bit(mrb_state *mrb, mrb_value self);

// GPIO
extern mrb_value mrb_mraa_gpio_init(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_edge_mode(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_isr(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_isr_exit(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_mode(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_dir(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_read(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_write(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_owner(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_use_mmaped(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_gpio_get_pin(mrb_state *mrb, mrb_value self);

// SPI
extern mrb_value mrb_mraa_spi_init(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_mode(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_frequency(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_transfer(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_transfer_byte(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_lsbmode(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_spi_bit_per_word(mrb_state *mrb, mrb_value self);

// I2C
extern mrb_value mrb_mraa_i2c_init(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_frequency(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_read(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_read_byte(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_read_reg(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_read_word_reg(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_write(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_write_byte(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_write_reg(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_write_word_reg(mrb_state *mrb, mrb_value self);
extern mrb_value mrb_mraa_i2c_address(mrb_state *mrb, mrb_value self);

void
mrb_mruby_mraa_gem_init(mrb_state* mrb){
    struct RClass *class_mraa;
    struct RClass *class_mraa_pwm;
    struct RClass *class_mraa_aio;
    struct RClass *class_mraa_gpio;
    struct RClass *class_mraa_spi;
    struct RClass *class_mraa_i2c;

    class_mraa = mrb_define_class(mrb, "Mraa", mrb->object_class);
    // COMMON
    mrb_define_class_method(mrb, class_mraa, "pin_mode_test", mrb_mraa_pin_mode_test, MRB_ARGS_REQ(2));
    mrb_define_class_method(mrb, class_mraa, "adc_raw_bits", mrb_mraa_adc_raw_bits, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, class_mraa, "adc_supported_bits", mrb_mraa_adc_supported_bits, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, class_mraa, "set_log_level", mrb_mraa_set_log_level, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_mraa, "get_platform_name", mrb_mraa_get_platform_name, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, class_mraa, "set_priority", mrb_mraa_set_priority, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_mraa, "version", mrb_mraa_version, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, class_mraa, "result_print", mrb_mraa_result_print, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_mraa, "get_platform_type", mrb_mraa_get_platform_type, MRB_ARGS_NONE());
    // constants
    // mraa_pinmodes
    mrb_define_const(mrb, class_mraa, "PIN_VALID", mrb_fixnum_value(MRAA_PIN_VALID));
    mrb_define_const(mrb, class_mraa, "PIN_GPIO", mrb_fixnum_value(MRAA_PIN_GPIO));
    mrb_define_const(mrb, class_mraa, "PIN_PWM", mrb_fixnum_value(MRAA_PIN_PWM));
    mrb_define_const(mrb, class_mraa, "PIN_FAST_GPIO", mrb_fixnum_value(MRAA_PIN_FAST_GPIO));
    mrb_define_const(mrb, class_mraa, "PIN_SPI", mrb_fixnum_value(MRAA_PIN_SPI));
    mrb_define_const(mrb, class_mraa, "PIN_I2C", mrb_fixnum_value(MRAA_PIN_I2C));
    mrb_define_const(mrb, class_mraa, "PIN_AIO", mrb_fixnum_value(MRAA_PIN_AIO));
    mrb_define_const(mrb, class_mraa, "PIN_UART", mrb_fixnum_value(MRAA_PIN_UART));
    // mraa_result
    mrb_define_const(mrb, class_mraa, "SUCCESS", mrb_fixnum_value(MRAA_SUCCESS));
    mrb_define_const(mrb, class_mraa, "ERROR_FEATURE_NOT_IMPLEMENTED", mrb_fixnum_value(MRAA_ERROR_FEATURE_NOT_IMPLEMENTED));
    mrb_define_const(mrb, class_mraa, "ERROR_FEATURE_NOT_SUPPORTED", mrb_fixnum_value(MRAA_ERROR_FEATURE_NOT_SUPPORTED));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_VERBOSITY_LEVEL", mrb_fixnum_value(MRAA_ERROR_INVALID_VERBOSITY_LEVEL));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_PARAMETER", mrb_fixnum_value(MRAA_ERROR_INVALID_PARAMETER));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_HANDLE", mrb_fixnum_value(MRAA_ERROR_INVALID_HANDLE));
    mrb_define_const(mrb, class_mraa, "ERROR_NO_RESOURCES", mrb_fixnum_value(MRAA_ERROR_NO_RESOURCES));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_RESOURCE", mrb_fixnum_value(MRAA_ERROR_INVALID_RESOURCE));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_QUEUE_TYPE", mrb_fixnum_value(MRAA_ERROR_INVALID_QUEUE_TYPE));
    mrb_define_const(mrb, class_mraa, "ERROR_NO_DATA_AVAILABLE", mrb_fixnum_value(MRAA_ERROR_NO_DATA_AVAILABLE));
    mrb_define_const(mrb, class_mraa, "ERROR_INVALID_PLATFORM", mrb_fixnum_value(MRAA_ERROR_INVALID_PLATFORM));
    mrb_define_const(mrb, class_mraa, "ERROR_PLATFORM_NOT_INITIALISED", mrb_fixnum_value(MRAA_ERROR_PLATFORM_NOT_INITIALISED));
    mrb_define_const(mrb, class_mraa, "ERROR_PLATFORM_ALREADY_INITIALISED", mrb_fixnum_value(MRAA_ERROR_PLATFORM_ALREADY_INITIALISED));
    mrb_define_const(mrb, class_mraa, "ERROR_UNSPECIFIED", mrb_fixnum_value(MRAA_ERROR_UNSPECIFIED));
    // mraa_platform
    mrb_define_const(mrb, class_mraa, "INTEL_GALILEO_GEN1", mrb_fixnum_value(MRAA_INTEL_GALILEO_GEN1));
    mrb_define_const(mrb, class_mraa, "INTEL_GALILEO_GEN2", mrb_fixnum_value(MRAA_INTEL_GALILEO_GEN2));
    mrb_define_const(mrb, class_mraa, "INTEL_EDISON_FAB_C", mrb_fixnum_value(MRAA_INTEL_EDISON_FAB_C));
    mrb_define_const(mrb, class_mraa, "INTEL_DE3815", mrb_fixnum_value(MRAA_INTEL_DE3815));
    mrb_define_const(mrb, class_mraa, "INTEL_MINNOWBOARD_MAX", mrb_fixnum_value(MRAA_INTEL_MINNOWBOARD_MAX));
    mrb_define_const(mrb, class_mraa, "RASPBERRY_PI_B", mrb_fixnum_value(MRAA_RASPBERRY_PI_B));
    mrb_define_const(mrb, class_mraa, "UNKNOWN_PLATFORM", mrb_fixnum_value(MRAA_UNKNOWN_PLATFORM));

    // PWM
    class_mraa_pwm = mrb_define_class_under(mrb, class_mraa, "Pwm", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_pwm, MRB_TT_DATA);
    // Pwm instance methods
    mrb_define_method(mrb, class_mraa_pwm, "initialize", mrb_mraa_pwm_init, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_pwm, "write", mrb_mraa_pwm_write, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "read", mrb_mraa_pwm_read, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_pwm, "period", mrb_mraa_pwm_period, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "period_ms", mrb_mraa_pwm_period_ms, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "period_us", mrb_mraa_pwm_period_us, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "pulsewidth", mrb_mraa_pwm_pulsewidth, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "pulsewidth_ms", mrb_mraa_pwm_pulsewidth_ms, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "pulsewidth_us", mrb_mraa_pwm_pulsewidth_us, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "enable", mrb_mraa_pwm_enable, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "owner", mrb_mraa_pwm_owner, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_pwm, "config_ms", mrb_mraa_pwm_config_ms, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_mraa_pwm, "config_percent", mrb_mraa_pwm_config_percent, MRB_ARGS_REQ(2));

    // AIO
    class_mraa_aio = mrb_define_class_under(mrb, class_mraa, "Aio", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_aio, MRB_TT_DATA);
    // Aio instance methods
    mrb_define_method(mrb, class_mraa_aio, "initialize", mrb_mraa_aio_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_aio, "read", mrb_mraa_aio_read, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_aio, "read_float", mrb_mraa_aio_read_float, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_aio, "set_bit", mrb_mraa_aio_set_bit, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_aio, "get_bit", mrb_mraa_aio_get_bit, MRB_ARGS_NONE());

    // GPIO
    class_mraa_gpio = mrb_define_class_under(mrb, class_mraa, "Gpio", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_gpio, MRB_TT_DATA);
    // Gpio instance methods
    mrb_define_method(mrb, class_mraa_gpio, "initialize", mrb_mraa_gpio_init, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_gpio, "edge_mode", mrb_mraa_gpio_edge_mode, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "isr", mrb_mraa_gpio_isr, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_gpio, "isr_exit", mrb_mraa_gpio_isr_exit, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_gpio, "mode", mrb_mraa_gpio_mode, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "dir", mrb_mraa_gpio_dir, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "read", mrb_mraa_gpio_read, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_gpio, "write", mrb_mraa_gpio_write, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "owner", mrb_mraa_gpio_owner, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "use_mmaped", mrb_mraa_gpio_use_mmaped, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "get_pin", mrb_mraa_gpio_get_pin, MRB_ARGS_OPT(1));
    // Gpio constants
    // gpio_mode
    mrb_define_const(mrb, class_mraa_gpio, "STRONG", mrb_fixnum_value(MRAA_GPIO_STRONG));
    mrb_define_const(mrb, class_mraa_gpio, "PULLUP", mrb_fixnum_value(MRAA_GPIO_PULLUP));
    mrb_define_const(mrb, class_mraa_gpio, "PULLDOWN", mrb_fixnum_value(MRAA_GPIO_PULLDOWN));
    // gpio_dir
    mrb_define_const(mrb, class_mraa_gpio, "HIZ", mrb_fixnum_value(MRAA_GPIO_HIZ));
    mrb_define_const(mrb, class_mraa_gpio, "OUT", mrb_fixnum_value(MRAA_GPIO_OUT));
    mrb_define_const(mrb, class_mraa_gpio, "IN", mrb_fixnum_value(MRAA_GPIO_IN));
    mrb_define_const(mrb, class_mraa_gpio, "OUT_HIGH", mrb_fixnum_value(MRAA_GPIO_OUT_HIGH));
    mrb_define_const(mrb, class_mraa_gpio, "OUT_LOW", mrb_fixnum_value(MRAA_GPIO_OUT_LOW));
    // gpio_edge
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_NONE", mrb_fixnum_value(MRAA_GPIO_EDGE_NONE));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_BOTH", mrb_fixnum_value(MRAA_GPIO_EDGE_BOTH));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_RISING", mrb_fixnum_value(MRAA_GPIO_EDGE_RISING));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_FALLING", mrb_fixnum_value(MRAA_GPIO_EDGE_FALLING));

    // SPI
    class_mraa_spi = mrb_define_class_under(mrb, class_mraa, "Spi", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_spi, MRB_TT_DATA);
    // Spi instance methods
    mrb_define_method(mrb, class_mraa_spi, "initialize", mrb_mraa_spi_init, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_spi, "mode", mrb_mraa_spi_mode, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_spi, "frequency", mrb_mraa_spi_frequency, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_spi, "transfer", mrb_mraa_spi_transfer, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_spi, "transfer_byte", mrb_mraa_spi_transfer_byte, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_spi, "lsbmode", mrb_mraa_spi_lsbmode, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_spi, "bit_per_word", mrb_mraa_spi_bit_per_word, MRB_ARGS_REQ(1));
    // Spi constants
    // spi_mode
    mrb_define_const(mrb, class_mraa_spi, "MODE0", mrb_fixnum_value(MRAA_SPI_MODE0));
    mrb_define_const(mrb, class_mraa_spi, "MODE1", mrb_fixnum_value(MRAA_SPI_MODE1));
    mrb_define_const(mrb, class_mraa_spi, "MODE2", mrb_fixnum_value(MRAA_SPI_MODE2));
    mrb_define_const(mrb, class_mraa_spi, "MODE3", mrb_fixnum_value(MRAA_SPI_MODE3));

    // I2C
    class_mraa_i2c = mrb_define_class_under(mrb, class_mraa, "I2c", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_i2c, MRB_TT_DATA);
    // I2c instance methods
    mrb_define_method(mrb, class_mraa_i2c, "initialize", mrb_mraa_i2c_init, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_i2c, "frequency", mrb_mraa_i2c_frequency, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_i2c, "read", mrb_mraa_i2c_read, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_i2c, "read_byte", mrb_mraa_i2c_read_byte, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_mraa_i2c, "read_reg", mrb_mraa_i2c_read_reg, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_i2c, "read_word_reg", mrb_mraa_i2c_read_word_reg, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_i2c, "write", mrb_mraa_i2c_write, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_i2c, "write_byte", mrb_mraa_i2c_write_byte, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_i2c, "write_reg", mrb_mraa_i2c_write_reg, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_mraa_i2c, "write_word_reg", mrb_mraa_i2c_write_word_reg, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_mraa_i2c, "address", mrb_mraa_i2c_address, MRB_ARGS_REQ(1));
    // I2c constants
    // i2c_mode
    mrb_define_const(mrb, class_mraa_i2c, "STD", mrb_fixnum_value(MRAA_I2C_STD));
    mrb_define_const(mrb, class_mraa_i2c, "FAST", mrb_fixnum_value(MRAA_I2C_FAST));
    mrb_define_const(mrb, class_mraa_i2c, "HIGH", mrb_fixnum_value(MRAA_I2C_HIGH));

    mraa_init();
}

void
mrb_mruby_mraa_gem_final(mrb_state* mrb){
    mraa_deinit();
}

