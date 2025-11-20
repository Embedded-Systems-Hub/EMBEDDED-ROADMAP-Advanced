#include "logger.h"
#include "actuators.h"
#include "storage.h"

#include <string.h>
#include <stdio.h>

static void logger_display_sink(const char *msg)
{
#ifdef TARGET_HOST
    FILE *f = fopen("display_log.txt", "a");
    if (f) {
        fprintf(f, "%s", msg);
        fclose(f);
    }
#else
    actuators_write("display", msg);
#endif
}

static void logger_flash_sink(const char *msg)
{
#ifdef TARGET_HOST
    FILE *f = fopen("flash_log.txt", "a");
    if (f) {
        fprintf(f, "%s", msg);
        fclose(f);
    }
#else
    storage_write("flash", 0, msg, strlen(msg)+1);
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
