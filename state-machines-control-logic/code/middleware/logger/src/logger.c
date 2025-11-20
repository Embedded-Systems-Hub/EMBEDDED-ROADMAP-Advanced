#include "logger.h"
#include <string.h>

static const LoggerSink_t *sink_table = NULL;
static size_t sink_count = 0;

void logger_init(void)
{
    sink_table = logger_get_sinks(&sink_count);
}

void logger_log(const char *msg)
{
    for (size_t i = 0; i < sink_count; i++)
        sink_table[i].write(msg);
}

void logger_log_to(const char *sink, const char *msg)
{
    for (size_t i = 0; i < sink_count; i++)
    {
        if (strcmp(sink_table[i].name, sink) == 0)
        {
            sink_table[i].write(msg);
            return;
        }
    }
}
