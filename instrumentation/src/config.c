#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "splunk.h"

struct kv {
    char *k;
    char *v;
};

void read_config_file(logger log, struct config *cfg, char *file_name);

void read_lines(struct config *cfg, FILE *fp);

void split_on_eq(char *string, struct kv *pair);

void load_config(logger log, struct config *cfg, char *file_name) {
    read_config_file(log, cfg, file_name);
    char log_line[MAX_LOG_LINE_LEN];
    if (cfg->service_name == NULL) {
        strcpy(log_line, "service_name not found in config, using default: ");
        strncat(log_line, default_service_name, MAX_LOG_LINE_LEN - strlen(log_line) - 1);
        log_debug(log, log_line);
        cfg->service_name = strdup(default_service_name);
    }
    if (cfg->java_agent_jar == NULL) {
        strcpy(log_line, "java_agent_jar not found in config, using default: ");
        strncat(log_line, default_jar_path, MAX_LOG_LINE_LEN - strlen(log_line) - 1);
        log_debug(log, log_line);
        cfg->java_agent_jar = strdup(default_jar_path);
    }
}

void read_config_file(logger log, struct config *cfg, char *file_name) {
    FILE *fp = fopen(file_name, "r");
    char log_line[MAX_LOG_LINE_LEN];
    if (fp == NULL) {
        strcpy(log_line, "file not found: ");
        strncat(log_line, file_name, MAX_LOG_LINE_LEN - strlen(log_line) - 1);
        log_debug(log, log_line);
        return;
    }

    strcpy(log_line, "reading config file: ");
    strncat(log_line, file_name, MAX_LOG_LINE_LEN - strlen(log_line) - 1);
    log_debug(log, log_line);
    read_lines(cfg, fp);
    fclose(fp);
}

void read_lines(struct config *cfg, FILE *fp) {
    static const int buflen = 255;
    char buf[buflen];
    struct kv pair = {.k = NULL, .v = NULL};
    while ((fgets(buf, buflen, fp)) != NULL) {
        buf[strcspn(buf, "\n")] = 0;
        split_on_eq(buf, &pair);
        if (streq(pair.k, "java_agent_jar")) {
            cfg->java_agent_jar = strdup(pair.v);
        } else if (streq(pair.k, "service_name")) {
            cfg->service_name = strdup(pair.v);
        }
    }
}

void split_on_eq(char *string, struct kv *pair) {
    pair->k = strsep(&string, "=");
    pair->v = string;
}

void free_config(struct config *cfg) {
    if (cfg->java_agent_jar != NULL) {
        free(cfg->java_agent_jar);
    }
    if (cfg->service_name != NULL) {
        free(cfg->service_name);
    }
}
