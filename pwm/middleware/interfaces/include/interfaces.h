#ifndef INTERFACES_H
#define INTERFACES_H

#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    const char *name;
    const void *iface;

} InterfaceEntry_t;

const status_t interfaces_get(const char *name, const void **iface);

const InterfaceEntry_t* interfaces_get_table(size_t *count);

#endif
