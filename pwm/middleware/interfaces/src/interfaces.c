#include "interfaces.h"
#include <string.h>
#include <stdio.h>

void interfaces_cfg_init(void);

static const InterfaceEntry_t *iface_table = NULL;
static size_t iface_count = 0;

const status_t interfaces_get(const char *name, const void **iface)
{
	status_t ret = STATUS_OK;

    CHECK_NULL(name);

	iface_table = interfaces_get_table(&iface_count);

	CHECK_NULL(iface_table);

    for (size_t i = 0; i < iface_count; i++)
    {
        if (strcmp(iface_table[i].name, name) == 0)
        {
        	CHECK_NULL(iface_table[i].iface);
        	*iface = iface_table[i].iface;
        }
    }

    return ret;
}
