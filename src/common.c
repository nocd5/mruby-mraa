#include <string.h>
#include <mruby.h>
#include <mraa.h>

mrb_value
mrb_mraa_pin_mode_test(mrb_state *mrb, mrb_value self){
    mrb_int pin;
    mrb_int mode;

    mraa_boolean_t is_enable;

    mrb_get_args(mrb, "ii", &pin, &mode);
    is_enable = mraa_pin_mode_test(pin, mode);

    return mrb_bool_value( is_enable != 0 );
}

mrb_value
mrb_mraa_adc_raw_bits(mrb_state *mrb, mrb_value self){
    int bits;

    bits = mraa_adc_raw_bits();

    return mrb_fixnum_value(bits);
}

mrb_value
mrb_mraa_adc_supported_bits(mrb_state *mrb, mrb_value self){
    int bits;

    bits = mraa_adc_supported_bits();

    return mrb_fixnum_value(bits);
}

mrb_value
mrb_mraa_set_log_level(mrb_state *mrb, mrb_value self){
    mrb_int level;

    mraa_result_t result;

    mrb_get_args(mrb, "i", &level);
    result = mraa_set_log_level(level);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_get_platform_name(mrb_state *mrb, mrb_value self){
    char* plat;

    plat = mraa_get_platform_name();

    return mrb_str_new(mrb, plat, strlen(plat));
}

mrb_value
mrb_mraa_set_priority(mrb_state *mrb, mrb_value self){
    mrb_int priority;

    int ret;

    mrb_get_args(mrb, "i", &priority);
    ret = mraa_set_priority(priority);

    return mrb_fixnum_value(ret);
}

mrb_value
mrb_mraa_version(mrb_state *mrb, mrb_value self){
    const char* ver;

    ver = mraa_get_version();

    return mrb_str_new(mrb, ver, strlen(ver));
}

mrb_value
mrb_mraa_result_print(mrb_state *mrb, mrb_value self){
    mrb_int result;

    mrb_get_args(mrb, "i", &result);

    mraa_result_print(result);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_get_platform_type(mrb_state *mrb, mrb_value self){
    mraa_platform_t plat;

    plat = mraa_get_platform_type();

    return mrb_fixnum_value(plat);
}

