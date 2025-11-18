#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>

typedef struct
{
    const char *name;
    void (*write)(const char *msg);

} LoggerSink_t;

void logger_init(void);
void logger_log(const char *msg);
void logger_log_to(const char *sink, const char *msg);

const LoggerSink_t* logger_get_sinks(size_t *count);

#endif
