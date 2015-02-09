#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
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

mrb_value
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

mrb_value
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

mrb_value
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

mrb_value
mrb_mraa_gpio_isr_exit(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mraa_gpio_isr_exit(pmmg->gpio);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_gpio_mode(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &edge_mode);
    mraa_gpio_mode(pmmg->gpio, edge_mode);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_gpio_dir(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int dir;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &dir);
    mraa_gpio_dir(pmmg->gpio, dir);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_gpio_read(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int val;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    val = mraa_gpio_read(pmmg->gpio);

    return mrb_fixnum_value(val);
}

mrb_value
mrb_mraa_gpio_write(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int val;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &val);
    mraa_gpio_write(pmmg->gpio, val);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_gpio_owner(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool owner;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &owner);
    mraa_gpio_owner(pmmg->gpio, owner);

    return mrb_nil_value();
}

mrb_value
mrb_mraa_gpio_use_mmaped(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool use_mmaped;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &use_mmaped);
    mraa_gpio_use_mmaped(pmmg->gpio, use_mmaped);

    return mrb_nil_value();
}

mrb_value
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

