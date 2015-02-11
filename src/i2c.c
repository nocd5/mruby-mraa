#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mraa.h>

static void
i2c_close(mrb_state *mrb, void *p){
    if (p != NULL){
        mraa_i2c_stop((mraa_i2c_context)p);
    }
}

static struct mrb_data_type mrb_mraa_i2c_ctx_type = {
    "MraaI2cContext", i2c_close
};

mrb_value
mrb_mraa_i2c_init(mrb_state *mrb, mrb_value self){
    mrb_int bus;
    mrb_bool raw;
    mraa_i2c_context i2c;

    raw = false;
    mrb_get_args(mrb, "i|b", &bus, &raw);

    if (raw == false){
        i2c = mraa_i2c_init(bus);
    }
    else {
        i2c = mraa_i2c_init_raw(bus);
    }

    if (i2c == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize BUS:%S.", mrb_fixnum_value(bus));
    }

    DATA_TYPE(self) = &mrb_mraa_i2c_ctx_type;
    DATA_PTR(self) = i2c;

    return self;
}

mrb_value
mrb_mraa_i2c_frequency(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int freq;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &freq);
    result = mraa_i2c_frequency(i2c, freq);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_address(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int addr;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &addr);
    result = mraa_i2c_address(i2c, addr);

    return mrb_fixnum_value(result);
}

