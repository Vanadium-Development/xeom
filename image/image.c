//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#include "image.h"
#include "../error/error.h"
#include "../math/utility.h"

#include <stdlib.h>
#include <stdio.h>

struct Pixel pixel_black()
{
        return (struct Pixel) {0, 0, 0};
}

void pixel_mul(struct Pixel *pixel, double d)
{
        pixel->r *= d;
        pixel->g *= d;
        pixel->b *= d;
}

int image_create(struct Image *image, uint64_t width, uint64_t height)
{
        if (!width || !height) {
                raise_error(XEOM_IMG_INVALID_DIMENSIONS);
                return -1;
        }

        image->width = width;
        image->height = height;
        image->pixels = malloc(width * height * sizeof(struct Pixel));

        image_fill(image, rgb(45, 52, 54));

        return 0;
}

void image_free(struct Image *image)
{
        free(image->pixels);
}

/**
 * A utility function to convert <code>(x, y)</code> coordinates into a raster index
 */
static uint64_t xy_to_i(struct Image *image, uint64_t x, uint64_t y)
{
        return image->width * y + x;
}

static int image_write_ppm(struct Image *image, FILE *file)
{
        fprintf(file, "P3\n%llu\n%llu\n255\n", image->width, image->height);

        for (uint64_t y = 0; y < image->height; y++)
                for (uint64_t x = 0; x < image->width; x++) {
                        struct Pixel px = image->pixels[xy_to_i(image, x, y)];
                        fprintf(file, "%d %d %d\n", (uint8_t) px.r, (uint8_t) px.g, (uint8_t) px.b);
                }

        return 0;
}

static int image_write_proprietary(struct Image *image, FILE *file)
{
        raise_error(XEOM_IMG_UNSUPPORTED_FORMAT);
        return -1;
}

int image_write(struct Image *image, enum OutputFormat format, const char *filename)
{
        FILE *fd = fopen(filename, "w");

        if (!fd) {
                raise_error(XEOM_FOPEN_FAIL);
                return -1;
        }

        int status;

        switch (format) {
                case FORMAT_PPM:
                        status = image_write_ppm(image, fd);
                        break;
                case FORMAT_PROPRIETARY:
                        status = image_write_proprietary(image, fd);
                        break;
                default:
                        raise_error(XEOM_IMG_INVALID_FORMAT);
                        status = -1;
                        break;
        }

        fclose(fd);

        return status;
}

inline int image_set(struct Image *image, uint64_t x, uint64_t y, struct Pixel color)
{
        if (x >= image->width || y >= image->height) {
                raise_error(XEOM_IMG_OUT_OF_BOUNDS);
                return -1;
        }

        image->pixels[xy_to_i(image, x, y)] = color;
        return 0;
}

inline int image_get(struct Image *image, uint64_t x, uint64_t y, struct Pixel *color)
{
        if (x >= image->width || y >= image->height) {
                raise_error(XEOM_IMG_OUT_OF_BOUNDS);
                return -1;
        }

        *color = image->pixels[xy_to_i(image, x, y)];
        return 0;
}

int image_fill(struct Image *image, struct Pixel color)
{
        for (uint64_t i = 0; i < image->width * image->height; i++)
                image->pixels[i] = color;

        return 0;
}

int image_add(struct Image *target, struct Image *another)
{
        if (target->width != another->width || target->height != another->height) {
                raise_error(XEOM_IMG_AVG_UNMATCHED_SIZES);
                return -1;
        }

        for (uint64_t i = 0; i < target->width * target->height; i++) {
                struct Pixel anotherPixel = another->pixels[i];

                target->pixels[i].r += anotherPixel.r;
                target->pixels[i].g += anotherPixel.g;
                target->pixels[i].b += anotherPixel.b;
        }

        return 0;
}

int image_output_average(struct Image *target, struct Image *source, uint64_t sample_count)
{
        if (target->width != source->width || target->height != source->height) {
                raise_error(XEOM_IMG_AVG_UNMATCHED_SIZES);
                return -1;
        }

        for (uint64_t i = 0; i < target->width * target->height; i++) {
                struct Pixel anotherPixel = source->pixels[i];

                target->pixels[i].r = anotherPixel.r / sample_count;
                target->pixels[i].g = anotherPixel.g / sample_count;
                target->pixels[i].b = anotherPixel.b / sample_count;
        }

        return 0;
}