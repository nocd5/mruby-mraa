#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mraa.h>

static void
uart_close(mrb_state *mrb, void *p){
    if (p != NULL){
        free(p);
    }
}

static struct mrb_data_type mrb_mraa_uart_ctx_type = {
    "MraaSpiContext", uart_close
};

mrb_value
mrb_mraa_uart_init(mrb_state *mrb, mrb_value self){
    mrb_int dev;
    mraa_uart_context uart;

    mrb_get_args(mrb, "i", &dev);

    uart = mraa_uart_init(dev);

    if (uart == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize DEV:%S.", mrb_fixnum_value(dev));
    }

    DATA_TYPE(self) = &mrb_mraa_uart_ctx_type;
    DATA_PTR(self) = uart;

    return self;
}

mrb_value
mrb_mraa_uart_get_dev_path(mrb_state *mrb, mrb_value self){
    mraa_uart_context uart;

    char *path;

    Data_Get_Struct(mrb, self, &mrb_mraa_uart_ctx_type, uart);

    path = mraa_uart_get_dev_path(uart);

    return mrb_str_new(mrb, path, strlen(path));
}
