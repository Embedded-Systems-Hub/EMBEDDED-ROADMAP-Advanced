#include "storage.h"
#include "interfaces.h"

#include "hal_flash.h"
#include <stdio.h>

typedef struct { const void *spi_ctx; uint8_t cs_pin; } Flash_Device_t;

static Flash_Device_t flash_dev;

static void flash_init_wrapper(void)
{
    flash_dev.spi_ctx = interfaces_get("spi1");
    flash_dev.cs_pin  = 5;

    hal_flash_init(&flash_dev);
}

static int flash_write_wrapper(uint32_t addr, const void *data, size_t size)
{
    return hal_flash_write(&flash_dev, addr, data, size);
}

static int flash_read_wrapper(uint32_t addr, void *data, size_t size)
{
    return hal_flash_read(&flash_dev, addr, data, size);
}

static StorageDesc_t storage_table[] =
{
    { "flash", flash_init_wrapper, flash_write_wrapper, flash_read_wrapper }
};

const StorageDesc_t* storage_get_table(size_t *count)
{
    *count = sizeof(storage_table) / sizeof(storage_table[0]);
    return storage_table;
}
