//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#ifndef XEOM_ARRAY_H
#define XEOM_ARRAY_H

#include <stdlib.h>

struct Array {
        size_t item_size;
        size_t length;
        size_t allocated_items;
        size_t grow_step;
        char *data;
};

int array_init(struct Array *array, size_t item_size);

int array_push(struct Array *array, void *item);

void *array_get(struct Array *array, size_t index);

int array_free(struct Array *array, void (*callback)(void *));

#endif //XEOM_ARRAY_H
