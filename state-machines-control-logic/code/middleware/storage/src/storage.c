#include "storage.h"
#include <string.h>

static const StorageDesc_t *table = NULL;
static size_t count = 0;

void storage_init(void)
{
    table = storage_get_table(&count);
    for (size_t i = 0; i < count; i++)
        if (table[i].init)
            table[i].init();
}

int storage_write(const char *name, uint32_t addr, const void *data, size_t size)
{
    for (size_t i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
            return table[i].write(addr, data, size);

    return -1;
}

int storage_read(const char *name, uint32_t addr, void *data, size_t size)
{
    for (size_t i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
            return table[i].read(addr, data, size);

    return -1;
}
