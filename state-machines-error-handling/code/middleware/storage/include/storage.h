#ifndef STORAGE_H
#define STORAGE_H

#include <stddef.h>
#include <stdint.h>
#include "error_codes.h"

/*
 * Descriptor for a storage backend.
 * Each storage device exposes:
 *   - a string name
 *   - an initialization callback
 *   - raw read/write functions
 *
 * The middleware uses this table to access storage devices by name.
 */
typedef struct
{
    const char *name;
    status_t (*init)(void);
    status_t (*write)(uint32_t addr, const void *data, size_t size);
    status_t (*read)(uint32_t addr, void *data, size_t size);

} StorageDesc_t;

/* Initializes all registered storage devices. */
status_t storage_init(void);

/* Write to a storage backend selected by name. */
status_t storage_write(const char *name, uint32_t addr, const void *data, size_t size);

/* Read from a storage backend selected by name. */
status_t storage_read (const char *name, uint32_t addr, void *data, size_t size);

/* Returns the static storage descriptor table. */
const StorageDesc_t* storage_get_table(size_t *count);

#endif
