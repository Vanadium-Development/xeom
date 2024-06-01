//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#ifndef XEOM_ARRAY_H
#define XEOM_ARRAY_H

#include <stdlib.h>

struct array {
        size_t item_size;
        size_t length;
        size_t allocated_items;
        size_t grow_step;
        char *data;
};

int array_init(struct array *array, size_t item_size);

int array_push(struct array *array, void *item);

void *array_get(struct array *array, size_t index);

int array_free(struct array *array, void (*callback)(void *));

#endif //XEOM_ARRAY_H
