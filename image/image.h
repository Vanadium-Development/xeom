//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#ifndef XEOM_IMAGE_H
#define XEOM_IMAGE_H

#include <inttypes.h>

struct Pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
};

struct Pixel pixel_black();

void pixel_mul(struct Pixel *pixel, double d);

struct Image {
        uint64_t width;
        uint64_t height;
        struct Pixel *pixels;
};

enum OutputFormat {
        FORMAT_PPM,
        FORMAT_PROPRIETARY
};

int image_create(struct Image *image, uint64_t width, uint64_t height);

void image_free(struct Image *image);

int image_write(struct Image *image, enum OutputFormat format, const char *filename);

int image_set(struct Image *image, uint64_t x, uint64_t y, struct Pixel color);

int image_get(struct Image *image, uint64_t x, uint64_t y, struct Pixel *color);

int image_fill(struct Image *image, struct Pixel color);

int image_average(struct Image *target, struct Image *another);

#endif //XEOM_IMAGE_H
