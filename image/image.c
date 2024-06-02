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
                        fprintf(file, "%d %d %d\n", px.r, px.g, px.b);
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