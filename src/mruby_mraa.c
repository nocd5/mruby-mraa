#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mraa.h>

static void
gpio_close(mrb_state *mrb, void *p){
    mraa_gpio_close((mraa_gpio_context)p);
}

static struct mrb_data_type mrb_mraa_gpio_ctx_type = {
    "MraaGpioContext", gpio_close
};

static mrb_value
mrb_mraa_gpio_init(mrb_state *mrb, mrb_value self){
    mrb_int pin;
    mrb_bool raw;
    mraa_gpio_context gpio;

    raw = false;
    mrb_get_args(mrb, "i|b", &pin, &raw);

    if (raw == false){
        gpio = mraa_gpio_init(pin);
    }
    else {
        gpio = mraa_gpio_init_raw(pin);
    }

    DATA_PTR(self) = gpio;
    DATA_TYPE(self) = &mrb_mraa_gpio_ctx_type;
    return self;
}

static mrb_value
mrb_mraa_gpio_dir(mrb_state *mrb, mrb_value self){
    mrb_int dir;
    mraa_gpio_context gpio;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, gpio);

    mrb_get_args(mrb, "i", &dir);
    mraa_gpio_dir(gpio, dir);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_write(mrb_state *mrb, mrb_value self){
    mrb_int val;
    mraa_gpio_context gpio;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, gpio);

    mrb_get_args(mrb, "i", &val);
    mraa_gpio_write(gpio, val);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_read(mrb_state *mrb, mrb_value self){
    mrb_int val;
    mraa_gpio_context gpio;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, gpio);

    val = mraa_gpio_read(gpio);
    return mrb_fixnum_value(val);
}

static mrb_value
mrb_mraa_version(mrb_state *mrb, mrb_value self){
    mrb_value result;
    const char* ver;
    ver = mraa_get_version();
    result = mrb_str_new(mrb, ver, strlen(ver));
    return result;
}

void
mrb_mruby_mraa_gem_init(mrb_state* mrb){
    struct RClass *class_mraa;
    struct RClass *class_mraa_gpio;

    class_mraa = mrb_define_class(mrb, "Mraa", mrb->object_class);
    mrb_define_class_method(mrb, class_mraa, "version", mrb_mraa_version, MRB_ARGS_NONE());

    // GPIO
    class_mraa_gpio = mrb_define_class_under(mrb, class_mraa, "Gpio", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_mraa_gpio, MRB_TT_DATA);
    // Gpio instance methods
    mrb_define_method(mrb, class_mraa_gpio, "initialize", mrb_mraa_gpio_init, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_mraa_gpio, "dir", mrb_mraa_gpio_dir, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "write", mrb_mraa_gpio_write, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_mraa_gpio, "read", mrb_mraa_gpio_read, MRB_ARGS_NONE());
    // Gpio constants
    // gpio_mode
    mrb_define_const(mrb, class_mraa_gpio, "STRONG", mrb_fixnum_value(MRAA_GPIO_STRONG));
    mrb_define_const(mrb, class_mraa_gpio, "PULLUP", mrb_fixnum_value(MRAA_GPIO_PULLUP));
    mrb_define_const(mrb, class_mraa_gpio, "PULLDOWN", mrb_fixnum_value(MRAA_GPIO_PULLDOWN));
    // gpio_dir
    mrb_define_const(mrb, class_mraa_gpio, "HIZ", mrb_fixnum_value(MRAA_GPIO_HIZ));
    mrb_define_const(mrb, class_mraa_gpio, "OUT", mrb_fixnum_value(MRAA_GPIO_OUT));
    mrb_define_const(mrb, class_mraa_gpio, "IN", mrb_fixnum_value(MRAA_GPIO_IN));
    // gpio_edge
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_NONE", mrb_fixnum_value(MRAA_GPIO_EDGE_NONE));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_BOTH", mrb_fixnum_value(MRAA_GPIO_EDGE_BOTH));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_RISING", mrb_fixnum_value(MRAA_GPIO_EDGE_RISING));
    mrb_define_const(mrb, class_mraa_gpio, "EDGE_FALLING", mrb_fixnum_value(MRAA_GPIO_EDGE_FALLING));

    mraa_init();
}

void
mrb_mruby_mraa_gem_final(mrb_state* mrb){
    mraa_deinit();
}

