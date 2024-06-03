//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_CALLBACK_H
#define XEOM_CALLBACK_H

#include <inttypes.h>

struct Intersection;
struct Scene;
struct Pixel;

typedef struct Pixel (*FragmentShader)(struct Intersection *, struct Scene *, uint64_t);

#endif //XEOM_CALLBACK_H
