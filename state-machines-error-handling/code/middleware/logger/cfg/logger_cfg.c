#include "logger.h"
#include "actuators.h"
#include "storage.h"

#include <string.h>
#include <stdio.h>

#ifndef LOG_MIN_SEVERITY_DISPLAY
#define LOG_MIN_SEVERITY_DISPLAY LOG_INFO
#endif

#ifndef LOG_MIN_SEVERITY_FLASH
#define LOG_MIN_SEVERITY_FLASH LOG_WARN
#endif

static void logger_display_sink(log_severity_t sev, const char *msg)
{
    if (sev < LOG_MIN_SEVERITY_DISPLAY)
        return;

#ifdef TARGET_HOST
    FILE *f = fopen("display_log.txt", "a");
    if (f) { fprintf(f, "%s", msg); fclose(f); }
#else
    (void)actuators_write("display", msg);
#endif
}

static void logger_flash_sink(log_severity_t sev, const char *msg)
{
    if (sev < LOG_MIN_SEVERITY_FLASH)
        return;

#ifdef TARGET_HOST
    FILE *f = fopen("flash_log.txt", "a");
    if (f) { fprintf(f, "%s", msg); fclose(f); }
#else
    (void)storage_write("flash", 0U, msg, strlen(msg) + 1U);
#endif
}

static LoggerSink_t sink_table[] =
{
    { "display", logger_display_sink },
    { "flash",   logger_flash_sink   }
};

const LoggerSink_t* logger_get_sinks(size_t *count)
{
    *count = sizeof(sink_table) / sizeof(sink_table[0]);
    return sink_table;
}
