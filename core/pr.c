//
// Created by Piotr Krzysztof Wyrwas on 04.06.24.
//

#include "pr.h"

#include "../error/error.h"

#include <pthread.h>

#include <stdio.h>

struct RenderThread {
        uint64_t number;
        const struct Scene *scene;
};

void *render(struct RenderThread *thread)
{
        printf("[Started thread %llu]\n", thread->number);

        struct Image outputImage;

        const struct Scene *scene = thread->scene;

        image_create(&outputImage, (uint64_t) scene->camera.width, (uint64_t) (scene->camera.width / scene->camera.aspect_ratio));

        if (scene_render(scene, &outputImage) < 0) {
                printf("Rendering failed: %s\n", xeom_string_error());
                return NULL;
        }

        char *filename = malloc(100);

        sprintf(filename, "parallel/sample_%llu.ppm", thread->number);

        image_write(&outputImage, FORMAT_PPM, filename);

        free(filename);

        image_free(&outputImage);

        printf("[Thread %llu finished]\n", thread->number);

        return NULL;
}

void render_simultaneously(const struct Scene* scene, uint64_t threads)
{
        pthread_t _threads[threads];
        struct RenderThread renderThreads[threads];

        printf("[Starting %llu rendering threads ...]\n", threads);

        for (uint64_t i = 0; i < threads; i ++) {
                renderThreads[i].scene = scene;
                renderThreads[i].number = i;

                pthread_create(&_threads[i], NULL, (void *) render, (void *) &renderThreads[i]);
        }

        for (uint64_t i = 0; i < threads; i ++)
                pthread_join(_threads[i], NULL);
}
