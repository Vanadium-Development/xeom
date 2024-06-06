//
// Created by Piotr Krzysztof Wyrwas on 04.06.24.
//

#ifndef XEOM_PR_H
#define XEOM_PR_H

#include <inttypes.h>

#include "scene.h"

struct Image render_simultaneously(struct Scene *scene, uint64_t samples);

#endif //XEOM_PR_H
