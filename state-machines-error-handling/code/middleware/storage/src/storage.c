#include "storage.h"
#include "error_codes.h"

#include <string.h>

/* Pointer to the statically defined storage descriptor table. */
static const StorageDesc_t *table = NULL;

/* Number of storage devices registered. */
static size_t count = 0;

status_t storage_init(void)
{
    status_t ret = STATUS_OK;

    table = storage_get_table(&count);
    CHECK_NULL(table);

    /*
     * Initialize all storage devices.
     * Each storage backend handles its own internal setup.
     */
    for (size_t i = 0; i < count; i++)
    {
        if (table[i].init != NULL)
        {
            ret = table[i].init();
            if (ret != STATUS_OK)
                break;
        }
    }

    return ret;
}

status_t storage_write(const char *name, uint32_t addr, const void *data, size_t size)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(name);
    CHECK_NULL(data);

    /* Find the storage backend by name. */
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(table[i].name, name) == 0)
        {
            if (table[i].write == NULL)
            {
                ret = STATUS_ERR_UNINIT;
            }
            else
            {
                ret = table[i].write(addr, data, size);
            }
            break;
        }
    }

    if (ret == STATUS_OK && table != NULL)
    {
        /*
         * If we iterated the full table without finding the name,
         * ret is still STATUS_OK but no write was attempted → invalid name.
         */
        int found = 0;
        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(table[i].name, name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
            ret = STATUS_ERR_INVALID_PARAM;
    }

    return ret;
}

status_t storage_read(const char *name, uint32_t addr, void *data, size_t size)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(name);
    CHECK_NULL(data);

    /* Linear search for storage backend. */
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(table[i].name, name) == 0)
        {
            if (table[i].read == NULL)
            {
                ret = STATUS_ERR_UNINIT;
            }
            else
            {
                ret = table[i].read(addr, data, size);
            }
            break;
        }
    }

    if (ret == STATUS_OK && table != NULL)
    {
        int found = 0;
        for (size_t i = 0; i < count; i++)
        {
            if (strcmp(table[i].name, name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
            ret = STATUS_ERR_INVALID_PARAM;
    }

    return ret;
}
