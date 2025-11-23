#include "storage.h"
#include "error_codes.h"

#include <stdio.h>
#include <string.h>

/*
 * Example: host-mode file storage backend.
 * Real hardware version would wrap flash/eeprom drivers.
 */

static status_t file_init(void)
{
#ifdef TARGET_HOST
    FILE *f = fopen("flash_log.txt", "wb");
    if (f)
        fclose(f);
#endif
    return STATUS_OK;
}

static status_t file_write(uint32_t addr, const void *data, size_t size)
{
    CHECK_NULL(data);

#ifdef TARGET_HOST
    FILE *f = fopen("flash_log.txt", "r+b");
    if (!f)
        return STATUS_ERR_HW_FAILURE;

    fseek(f, addr, SEEK_SET);
    fwrite(data, 1, size, f);
    fclose(f);
#endif

    return STATUS_OK;
}

static status_t file_read(uint32_t addr, void *data, size_t size)
{
    CHECK_NULL(data);

#ifdef TARGET_HOST
    FILE *f = fopen("flash_log.txt", "rb");
    if (!f)
        return STATUS_ERR_HW_FAILURE;

    fseek(f, addr, SEEK_SET);
    fread(data, 1, size, f);
    fclose(f);
#endif

    return STATUS_OK;
}

static const StorageDesc_t storage_table[] =
{
    { "flash", file_init, file_write, file_read }
};

const StorageDesc_t* storage_get_table(size_t *count)
{
    *count = sizeof(storage_table) / sizeof(storage_table[0]);
    return storage_table;
}
