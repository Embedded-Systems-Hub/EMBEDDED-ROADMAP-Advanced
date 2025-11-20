#include "interfaces.h"
#include <string.h>
#include <stdio.h>

void interfaces_cfg_init(void);

typedef struct
{
    const char *name;
    const void *iface;

} InterfaceEntry_t;

static InterfaceEntry_t table[16];
static size_t count = 0;

void interfaces_register(const char *name, const void *iface)
{
    if (count < sizeof(table) / sizeof(table[0]))
    {
        table[count].name  = name;
        table[count].iface = iface;
        count++;
    }
}

const void* interfaces_get(const char *name)
{
    for (size_t i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
            return table[i].iface;

    return NULL;
}

void interfaces_init(void)
{
    interfaces_cfg_init();
}
