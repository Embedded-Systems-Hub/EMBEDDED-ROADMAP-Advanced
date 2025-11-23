#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum
{
    STATUS_OK = 0,
    STATUS_ERR_UNKNOWN,
    STATUS_ERR_INVALID_PARAM,
    STATUS_ERR_NULL_PTR,
    STATUS_ERR_TIMEOUT,
    STATUS_ERR_OUT_OF_RANGE,
    STATUS_ERR_UNINIT,
    STATUS_ERR_HW_FAILURE
} status_t;

#define CHECK_NULL(ptr)                            \
    do {                                           \
        if ((ptr) == NULL) {                       \
            return STATUS_ERR_NULL_PTR;            \
        }                                          \
    } while (0)

#define CHECK_RANGE(val, min, max)                 \
    do {                                           \
        if (((val) < (min)) || ((val) > (max))) {  \
            return STATUS_ERR_OUT_OF_RANGE;        \
        }                                          \
    } while (0)

#define CHECK_STATUS(expr)                         \
    do {                                           \
        status_t _st = (expr);                     \
        if (_st != STATUS_OK) {                    \
            return _st;                            \
        }                                          \
    } while (0)

#endif /* ERROR_CODES_H */
