//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_SCENE_H
#define XEOM_SCENE_H

#include "../mm/array.h"
#include "camera.h"
#include "../image/image.h"

struct Scene {
        struct Array shapes;
        struct Camera camera;
};

void scene_create(struct Scene *scene);

void scene_free(struct Scene *scene);

int scene_render(struct Scene *scene, struct Image *output);

#endif //XEOM_SCENE_H