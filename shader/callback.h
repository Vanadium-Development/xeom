//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_CALLBACK_H
#define XEOM_CALLBACK_H

struct Intersection;
struct Scene;
struct Pixel;

typedef struct Pixel (*FragmentShader)(struct Intersection *, struct Scene *);

#endif //XEOM_CALLBACK_H
