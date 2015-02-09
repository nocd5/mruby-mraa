#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mraa.h>

typedef struct {
    mrb_state *mrb;
    mrb_value func;
    mrb_value args;
} gpio_isr_args_t;

typedef struct {
    mraa_gpio_context gpio;
    gpio_isr_args_t *gpio_isr_args;
} mrb_mraa_gpio_t;

static void
gpio_close(mrb_state *mrb, void *p){
    mrb_mraa_gpio_t *pmmg;
    pmmg = (mrb_mraa_gpio_t *)p;

    if (pmmg != NULL){
        if (pmmg->gpio_isr_args != NULL){
            mrb_free(mrb, pmmg->gpio_isr_args);
        }
        mraa_gpio_close(pmmg->gpio);
        mrb_free(mrb, p);
    }
}

static struct mrb_data_type mrb_mraa_gpio_ctx_type = {
    "MraaGpioContext", gpio_close
};

static mrb_value
mrb_mraa_gpio_init(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
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

    pmmg = (mrb_mraa_gpio_t *)mrb_malloc(mrb, sizeof(mrb_mraa_gpio_t));
    pmmg->gpio = gpio;
    pmmg->gpio_isr_args = NULL;

    DATA_PTR(self) = pmmg;
    DATA_TYPE(self) = &mrb_mraa_gpio_ctx_type;

    return self;
}

static mrb_value
mrb_mraa_gpio_edge_mode(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &edge_mode);
    mraa_gpio_edge_mode(pmmg->gpio, edge_mode);

    return mrb_nil_value();
}

static void
gpio_interrupt(void *args)
{
    mrb_yield(
        ((gpio_isr_args_t *)args)->mrb,
        ((gpio_isr_args_t *)args)->func,
        ((gpio_isr_args_t *)args)->args);
}

static mrb_value
mrb_mraa_gpio_isr(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    pmmg->gpio_isr_args =
        (gpio_isr_args_t*)mrb_malloc(mrb, sizeof(gpio_isr_args_t));
    memset(pmmg->gpio_isr_args, 0, sizeof(gpio_isr_args_t));

    pmmg->gpio_isr_args->mrb = mrb;

    mrb_get_args(mrb, "io|o",
            &edge_mode, &pmmg->gpio_isr_args->func, &pmmg->gpio_isr_args->args);

    mraa_gpio_isr(pmmg->gpio, edge_mode, gpio_interrupt, (void *)pmmg->gpio_isr_args);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_isr_exit(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mraa_gpio_isr_exit(pmmg->gpio);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_mode(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &edge_mode);
    mraa_gpio_mode(pmmg->gpio, edge_mode);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_dir(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int dir;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &dir);
    mraa_gpio_dir(pmmg->gpio, dir);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_read(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int val;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    val = mraa_gpio_read(pmmg->gpio);

    return mrb_fixnum_value(val);
}

static mrb_value
mrb_mraa_gpio_write(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int val;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &val);
    mraa_gpio_write(pmmg->gpio, val);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_owner(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool owner;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &owner);
    mraa_gpio_owner(pmmg->gpio, owner);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_use_mmaped(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool use_mmaped;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &use_mmaped);
    mraa_gpio_use_mmaped(pmmg->gpio, use_mmaped);

    return mrb_nil_value();
}

static mrb_value
mrb_mraa_gpio_get_pin(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int pin;
    mrb_bool raw;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    raw = false;
    mrb_get_args(mrb, "|b", &raw);

    if (raw == false){
        pin = mraa_gpio_get_pin(pmmg->gpio);
    }
    else {
        pin = mraa_gpio_get_pin_raw(pmmg->gpio);
    }

    return mrb_fixnum_value(pin);
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

