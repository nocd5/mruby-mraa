#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <mruby/object.h>
#include <mraa.h>

typedef struct {
    mrb_state *mrb;
    mrb_value self;
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
        if (pmmg->gpio != NULL){
            mraa_gpio_close(pmmg->gpio);
        }
        mrb_free(mrb, pmmg);
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

    pmmg = (mrb_mraa_gpio_t *)mrb_malloc(mrb, sizeof(mrb_mraa_gpio_t));
    memset(pmmg, 0, sizeof(mrb_mraa_gpio_t));
    DATA_TYPE(self) = &mrb_mraa_gpio_ctx_type;
    DATA_PTR(self) = pmmg;

    raw = false;
    mrb_get_args(mrb, "i|b", &pin, &raw);

    if (raw == false){
        pmmg->gpio = mraa_gpio_init(pin);
    }
    else {
        pmmg->gpio = mraa_gpio_init_raw(pin);
    }

    if (pmmg->gpio == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize PIN:%S.", mrb_fixnum_value(pin));
    }

    return self;
}

mrb_value
mrb_mraa_gpio_edge_mode(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &edge_mode);
    result = mraa_gpio_edge_mode(pmmg->gpio, edge_mode);

    return mrb_fixnum_value(result);
}

static void
gpio_interrupt(void *p)
{
    mrb_state *mrb;
    mrb_value self;
    mrb_value func;
    mrb_value args;
    int ai;

    mrb = ((gpio_isr_args_t *)p)->mrb;
    self = ((gpio_isr_args_t *)p)->self;

    ai = mrb_gc_arena_save(mrb);

    func = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "isr_func"));
    args = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "isr_args"));

    mrb_yield(mrb, func, args);

    mrb_gc_arena_restore(mrb, ai);
}

mrb_value
mrb_mraa_gpio_isr(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;
    mrb_value func;
    mrb_value args;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    pmmg->gpio_isr_args =
        (gpio_isr_args_t *)mrb_malloc(mrb, sizeof(gpio_isr_args_t));
    memset(pmmg->gpio_isr_args, 0, sizeof(gpio_isr_args_t));

    pmmg->gpio_isr_args->mrb = mrb;
    pmmg->gpio_isr_args->self = self;

    args = mrb_nil_value();
    mrb_get_args(mrb, "io|o", &edge_mode, &func, &args);
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "isr_func"), func);
    if (!mrb_nil_p(args)){
        mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "isr_args"), args);
    }

    result = mraa_gpio_isr(pmmg->gpio, edge_mode, gpio_interrupt, (void *)pmmg->gpio_isr_args);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_gpio_isr_exit(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    result = mraa_gpio_isr_exit(pmmg->gpio);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_gpio_mode(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int edge_mode;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &edge_mode);
    result = mraa_gpio_mode(pmmg->gpio, edge_mode);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_gpio_dir(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_int dir;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &dir);
    result = mraa_gpio_dir(pmmg->gpio, dir);

    return mrb_fixnum_value(result);
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

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "i", &val);
    result = mraa_gpio_write(pmmg->gpio, val);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_gpio_owner(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool owner;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &owner);
    result = mraa_gpio_owner(pmmg->gpio, owner);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_gpio_use_mmaped(mrb_state *mrb, mrb_value self){
    mrb_mraa_gpio_t *pmmg;
    mrb_bool use_mmaped;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_gpio_ctx_type, pmmg);

    mrb_get_args(mrb, "b", &use_mmaped);
    result = mraa_gpio_use_mmaped(pmmg->gpio, use_mmaped);

    return mrb_fixnum_value(result);
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

