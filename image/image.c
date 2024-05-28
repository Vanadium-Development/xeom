//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#include "image.h"
#include "../error/error.h"

#include <stdlib.h>
#include <stdio.h>

int image_create(struct image *image, uint64_t width, uint64_t height)
{
        if (!width || !height) {
                raise_error(XEOM_IMG_INVALID_DIMENSIONS);
                return -1;
        }

        image->width = width;
        image->height = height;
        image->pixels = calloc(width * height, sizeof(struct pixel));
        return 0;
}

void image_free(struct image *image)
{
        free(image->pixels);
}

/**
 * A utility function to convert <code>(x, y)</code> coordinates into a raster index
 */
static uint64_t xy_to_i(struct image *image, uint64_t x, uint64_t y)
{
        return image->width * y + x;
}

static int image_write_ppm(struct image *image, FILE *file)
{
        fprintf(file, "P3\n%llu\n%llu\n255\n", image->width, image->height);

        for (uint64_t y = 0; y < image->height; y++)
                for (uint64_t x = 0; x < image->width; x++) {
                        struct pixel px = image->pixels[xy_to_i(image, x, y)];
                        fprintf(file, "%d %d %d\n", px.r, px.g, px.b);
                }

        return 0;
}

static int image_write_proprietary(struct image *image, FILE *file)
{
        raise_error(XEOM_IMG_UNSUPPORTED_FORMAT);
        return -1;
}

int image_write(struct image *image, enum output_format format, const char *filename)
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

inline int image_set(struct image *image, uint64_t x, uint64_t y, struct pixel color)
{
        if (x >= image->width || y >= image->height) {
                raise_error(XEOM_IMG_OUT_OF_BOUNDS);
                return -1;
        }

        image->pixels[xy_to_i(image, x, y)] = color;
        return 0;
}

inline int image_get(struct image *image, uint64_t x, uint64_t y, struct pixel *color)
{
        if (x >= image->width || y >= image->height) {
                raise_error(XEOM_IMG_OUT_OF_BOUNDS);
                return -1;
        }

        *color = image->pixels[xy_to_i(image, x, y)];
        return 0;
}
