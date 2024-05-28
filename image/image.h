//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#ifndef XEOM_IMAGE_H
#define XEOM_IMAGE_H

#include <inttypes.h>

struct pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
};

struct image {
        uint64_t width;
        uint64_t height;
        struct pixel *pixels;
};

enum output_format {
        FORMAT_PPM,
        FORMAT_PROPRIETARY
};

int image_create(struct image *image, uint64_t width, uint64_t height);

void image_free(struct image *image);

int image_write(struct image *image, enum output_format format, const char *filename);

int image_set(struct image *image, uint64_t x, uint64_t y, struct pixel color);

int image_get(struct image *image, uint64_t x, uint64_t y, struct pixel *color);

#endif //XEOM_IMAGE_H
