#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>
#include "error_codes.h"

/*
 * Severity levels used by the logger.
 * Order matters only if sinks decide to filter messages internally.
 */
typedef enum
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} log_severity_t;

/*
 * A logging sink processes log messages.
 * Each sink has:
 *   - a string name for targeted logging
 *   - a write callback receiving severity and message
 */
typedef struct
{
    const char *name;
    void (*write)(log_severity_t sev, const char *msg);
} LoggerSink_t;

/*
 * Initializes all registered sinks (obtained from logger_cfg).
 * Must be called before logger_log() is used.
 */
void logger_init(void);

/*
 * Broadcasts a log message to ALL registered sinks.
 */
status_t logger_log(log_severity_t sev, const char *fmt, ...);

/*
 * Sends a log message only to the sink whose name matches `sink`.
 * If the name is not found, nothing happens silently.
 */
status_t logger_log_to(const char *sink, log_severity_t sev, const char *fmt, ...);

/*
 * Returns the static sink table declared in logger_cfg.
 */
const LoggerSink_t* logger_get_sinks(size_t *count);

#endif
