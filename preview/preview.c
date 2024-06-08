//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifdef XEOM_USE_GUI

#include "preview.h"

void preview_render(struct Preview *preview)
{
        uint64_t width = preview->image->width,
                height = preview->image->height;

        for (uint64_t i = 0; i < width * height; i++) {
                uint64_t y = i / width;
                uint64_t x = i % width;

                struct Pixel px;

                if (image_get(preview->image, x, y, &px) < 0) {
                        return;
                }

                SDL_SetRenderDrawColor(preview->renderer, (uint8_t) px.r, (uint8_t) px.g, (uint8_t) px.b,
                                       SDL_ALPHA_OPAQUE);
                SDL_RenderDrawPoint(preview->renderer, x, y);
        }

        SDL_RenderPresent(preview->renderer);
        SDL_UpdateWindowSurface(preview->window);
}

int preview_tick(struct Preview *preview)
{
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
                if (evt.type == SDL_QUIT) {
                        preview_close_and_destroy(preview);
                        return -1;
                }
        }

        preview_render(preview);

        return 0;
}

int preview_create(struct Preview *preview, struct Image *image)
{
        preview->image = image;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
                printf("Could not initialize Preview: %s\n", SDL_GetError());
                return -1;
        }

        char *title = calloc(100, sizeof(char));

        sprintf(title, "Vanadium Xeom (%llu x %llu)", image->width, image->height);

        preview->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           image->width, image->height, SDL_WINDOW_SHOWN);

        free(title);

        if (!preview->window) {
                printf("Could not create Preview window: %s\n", SDL_GetError());
                return -1;
        }

        preview->renderer = SDL_CreateRenderer(preview->window, 0, SDL_RENDERER_ACCELERATED);

        if (!preview->renderer) {
                printf("Could not create software renderer: %s\n", SDL_GetError());
                SDL_DestroyWindow(preview->window);
                return -1;
        }

        return 0;
}

void preview_close_and_destroy(struct Preview *preview)
{
        SDL_DestroyRenderer(preview->renderer);
        SDL_DestroyWindow(preview->window);
}

#endif