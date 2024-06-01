#include <stdio.h>

#include "../image/image.h"

#include "../error/error.h"

#include "../preview/preview.h"

int main(void)
{
        struct image img;
        image_create(&img, 1000, 700);

        struct preview prev;
        preview_create(&prev, &img);

        for (uint64_t i = 0; i < 1000 * 700; i++) {
                if (image_set(&img, i % 1000, i / 1000, (struct pixel) {.r = 255}) < 0) {
                        printf("%s\n", xeom_string_error());
                }
        }

        if (image_write(&img, FORMAT_PPM, "image.ppm") < 0) {
                printf("%s\n", xeom_string_error());
        }

        while (preview_tick(&prev) == 0);

        image_free(&img);
        return 0;
}
