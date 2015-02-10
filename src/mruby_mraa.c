#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mraa.h>

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

    mraa_init();
}

void
mrb_mruby_mraa_gem_final(mrb_state* mrb){
    mraa_deinit();
}

