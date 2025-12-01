#ifndef HAL_LDR_H
#define HAL_LDR_H

#include <stdint.h>
#include "error_codes.h"

typedef struct
{
	status_t (*init)(void *dev);
	status_t (*read)(void *dev, void *out);
} HAL_Potentiometer_Driver_t;

status_t hal_potentiometer_init(void *dev);
status_t hal_potentiometer_read(void *dev, void *out);

const HAL_Potentiometer_Driver_t* hal_potentiometer_get_drv(void);

#endif
