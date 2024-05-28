//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_PREVIEW_H
#define XEOM_PREVIEW_H

#include <SDL2/SDL.h>

#include "../image/image.h"

struct preview {
        struct image *image;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

int preview_create(struct preview *preview, struct image *image);

void preview_render(struct preview *preview);

int preview_tick(struct preview *preview);

void preview_close_and_destroy(struct preview *preview);

#endif //XEOM_PREVIEW_H
