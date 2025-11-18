#ifndef STORAGE_H
#define STORAGE_H

#include <stddef.h>
#include <stdint.h>

typedef struct
{
    const char *name;
    void (*init)(void);
    int  (*write)(uint32_t addr, const void *data, size_t size);
    int  (*read)(uint32_t addr, void *data, size_t size);

} StorageDesc_t;

void storage_init(void);
int  storage_write(const char *name, uint32_t addr, const void *data, size_t size);
int  storage_read (const char *name, uint32_t addr, void *data, size_t size);

const StorageDesc_t* storage_get_table(size_t *count);

#endif
