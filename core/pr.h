//
// Created by Piotr Krzysztof Wyrwas on 04.06.24.
//

#ifndef XEOM_PR_H
#define XEOM_PR_H

#include <inttypes.h>

#include "scene.h"

void render_simultaneously(const struct Scene *scene, uint64_t threads);

#endif //XEOM_PR_H
