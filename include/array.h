#ifndef bf_array_h
#define bf_array_h

#include <stdlib.h>

#define array(T, name)                                                         \
    struct {                                                                   \
        T *values;                                                             \
        size_t num;                                                            \
        size_t cap;                                                            \
    } name

#define array_init(T, arr, n)                                                  \
    do {                                                                       \
        (arr)->values = calloc((n), sizeof(T));                                \
        (arr)->num = 0;                                                        \
        (arr)->cap = (n);                                                      \
    } while (0)

#define array_resize(arr, n)                                                   \
    do {                                                                       \
        (arr)->cap = n;                                                        \
        (arr)->values = realloc((arr)->values, sizeof((arr)->values[0])*(n));  \
    } while (0)

#define array_free(arr)                                                        \
    do {                                                                       \
        free((arr)->values);                                                   \
        (arr)->cap = 0;                                                        \
        (arr)->num = 0;                                                        \
        (arr)->values = NULL;                                                  \
    } while (0)

#define array_add(arr, elem)                                                   \
    do {                                                                       \
        if ((arr)->num + 1 > (arr)->cap) {                                     \
            (arr)->cap = (arr)->cap < 8 ? 8 : (arr)->cap * 2;                  \
            array_resize((arr), (arr)->cap);                                   \
        }                                                                      \
        (arr)->values[(arr)->num++] = (elem);                                  \
    } while (0)

#define array_pop(arr) (arr)->values[--(arr)->num]

#endif
