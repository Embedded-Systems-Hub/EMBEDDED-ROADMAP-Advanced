#ifndef INTERFACES_H
#define INTERFACES_H

void interfaces_init(void);
void interfaces_register(const char *name, const void *iface);
const void* interfaces_get(const char *name);

#endif
