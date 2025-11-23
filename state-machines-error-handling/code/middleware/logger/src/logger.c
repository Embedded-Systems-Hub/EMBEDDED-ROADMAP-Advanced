#include "logger.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static const LoggerSink_t *sink_table = NULL;
static size_t sink_count = 0U;

void logger_init(void)
{
    sink_table = logger_get_sinks(&sink_count);
}

status_t logger_log(log_severity_t sev, const char *fmt, ...)
{
    CHECK_NULL(fmt);
    CHECK_RANGE(sev, LOG_DEBUG, LOG_ERROR);

    if (!sink_table || sink_count == 0U)
        return STATUS_ERR_UNINIT;

    char buffer[128];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    for (size_t i = 0; i < sink_count; i++)
        sink_table[i].write(sev, buffer);

    return STATUS_OK;
}

status_t logger_log_to(const char *sink, log_severity_t sev, const char *fmt, ...)
{
    CHECK_NULL(sink);
    CHECK_NULL(fmt);
    CHECK_RANGE(sev, LOG_DEBUG, LOG_ERROR);

    if (!sink_table || sink_count == 0U)
        return STATUS_ERR_UNINIT;

    char buffer[128];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    for (size_t i = 0; i < sink_count; i++)
    {
        if (strcmp(sink_table[i].name, sink) == 0)
        {
            sink_table[i].write(sev, buffer);
            return STATUS_OK;
        }
    }

    return STATUS_ERR_INVALID_PARAM;
}
