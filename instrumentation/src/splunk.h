#ifndef SPLUNK_INSTRUMENTATION_SPLUNK_H
#define SPLUNK_INSTRUMENTATION_SPLUNK_H

#include "logger.h"
#include "config.h"
#include "cmdline_reader.h"
#include <stdbool.h>

static char *const disable_env_var_name = "DISABLE_SPLUNK_AUTOINSTRUMENTATION";

typedef bool (*has_access_func_t)(const char *);

typedef void (*load_config_func_t)(logger log, struct config *, char *);

void auto_instrument(
        logger log,
        has_access_func_t has_access,
        const char *program_name,
        load_config_func_t load_config_func,
        cmdline_reader cr
);

bool streq(const char *expected, const char *actual);

#endif //SPLUNK_INSTRUMENTATION_SPLUNK_H
