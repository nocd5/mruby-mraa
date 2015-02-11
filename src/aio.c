#include <mruby.h>
#include <mruby/data.h>
#include <mraa.h>

static void
aio_close(mrb_state *mrb, void *p){
    if (p != NULL){
        mraa_aio_close((mraa_aio_context)p);
    }
}

static struct mrb_data_type mrb_mraa_aio_ctx_type = {
    "MraaAioContext", aio_close
};

mrb_value
mrb_mraa_aio_init(mrb_state *mrb, mrb_value self){
    mrb_int pin;
    mraa_aio_context aio;

    mrb_get_args(mrb, "i", &pin);

    aio = mraa_aio_init(pin);

    if (aio == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize PIN:%S.", mrb_fixnum_value(pin));
    }

    DATA_TYPE(self) = &mrb_mraa_aio_ctx_type;
    DATA_PTR(self) = aio;

    return self;
}

mrb_value
mrb_mraa_aio_read(mrb_state *mrb, mrb_value self){
    mraa_aio_context aio;
    mrb_int val;

    Data_Get_Struct(mrb, self, &mrb_mraa_aio_ctx_type, aio);

    val = mraa_aio_read(aio);

    return mrb_fixnum_value(val);
}

mrb_value
mrb_mraa_aio_read_float(mrb_state *mrb, mrb_value self){
    mraa_aio_context aio;
    float val;

    Data_Get_Struct(mrb, self, &mrb_mraa_aio_ctx_type, aio);

    val = mraa_aio_read_float(aio);

    return mrb_float_value(mrb, val);
}

mrb_value
mrb_mraa_aio_set_bit(mrb_state *mrb, mrb_value self){
    mraa_aio_context aio;
    mrb_int bits;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_aio_ctx_type, aio);

    mrb_get_args(mrb, "i", &bits);
    result = mraa_aio_set_bit(aio, bits);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_aio_get_bit(mrb_state *mrb, mrb_value self){
    mraa_aio_context aio;

    mrb_int bits;

    Data_Get_Struct(mrb, self, &mrb_mraa_aio_ctx_type, aio);

    bits = mraa_aio_get_bit(aio);

    return mrb_fixnum_value(bits);
}

