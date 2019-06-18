#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t data_t;

typedef struct
{
    size_t len;
    data_t* data;
} vec_rec, *vec_ptr;

vec_ptr
new_vec(size_t len)
{
    vec_ptr result = (vec_ptr)malloc(sizeof(vec_rec));
    data_t* data = NULL;

    if (!result) return NULL;

    result->len = len;

    if (len > 0) {
        data = (data_t*)calloc(len, sizeof(data_t));
        if (!data) {
            free((void*)result);
            return NULL;
        }
    }

    result->data = data;
    return result;
}

int
get_vec_element(vec_ptr v, size_t index, data_t* dest)
{
    if (index < 0 || index >= v->len)
        return 0;

    *dest = v->data[index];
    return 1;
}

size_t
vec_length(vec_ptr v)
{
    return v->len;
}

size_t*
get_vec_start(vec_ptr v)
{
    return v->data;
}
