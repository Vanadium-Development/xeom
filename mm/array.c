//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#include "array.h"

#include <string.h>

int _array_perform_alloc(struct Array *array)
{
#if defined (__APPLE__)
        #define _realloc reallocf
#else
        #define _realloc realloc
#endif

        array->data = _realloc(array->data, array->allocated_items * array->item_size);

        return array->data ? 0 : -1;
}

int _array_check_resize(struct Array *array)
{
        if (array->length < array->allocated_items)
                return 0;

        array->allocated_items += array->grow_step;
        return _array_perform_alloc(array);
}

int array_init(struct Array *array, size_t item_size)
{
        array->item_size = item_size;
        array->length = 0;
        array->grow_step = 10;
        array->allocated_items = array->grow_step;
        array->data = NULL;

        if (_array_perform_alloc(array) < 0)
                return -1;

        return 0;
}

int array_push(struct Array *array, void *item)
{
        if (_array_check_resize(array) < 0)
                return -1;

        memcpy(array->data + array->item_size * (array->length++), item, array->item_size);

        return 0;
}

void *array_get(struct Array *array, size_t index)
{
        if (index >= array->length)
                return NULL;

        return &array->data[array->item_size * index];
}

int array_free(struct Array *array, void (*callback)(void *))
{
        if (!callback)
                goto no_callback;

        for (size_t i = 0; i < array->length; i++) {
                void *item = array_get(array, i);
                if (!item)
                        break;
                callback(item);
        }

        no_callback:
        free(array->data);
        memset(array, 0, sizeof(struct Array));
        return 0;
}