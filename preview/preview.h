//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_PREVIEW_H
#define XEOM_PREVIEW_H

#ifdef XEOM_USE_GUI

#include <SDL2/SDL.h>

#include "../image/image.h"

struct Preview {
        struct Image *image;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

int preview_create(struct Preview *preview, struct Image *image);

void preview_render(struct Preview *preview);

int preview_tick(struct Preview *preview);

void preview_close_and_destroy(struct Preview *preview);

#endif

#endif //XEOM_PREVIEW_H
