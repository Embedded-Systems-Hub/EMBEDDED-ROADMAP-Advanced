#ifndef INTERFACES_H
#define INTERFACES_H

/*
 * Initializes all interface contexts defined in interfaces_cfg.
 * Must be called before any component requests an interface.
 */
void interfaces_init(void);

/*
 * Registers a hardware interface under a string name.
 * The middleware/HAL can later retrieve the same pointer by name.
 */
void interfaces_register(const char *name, const void *iface);

/*
 * Retrieves a previously registered interface context by name.
 * Returns NULL if the name is not found.
 */
const void* interfaces_get(const char *name);

#endif
