//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_SHAPE_H
#define XEOM_SHAPE_H

#include "vec3d.h"

enum shape_type {
        SHAPE_SPHERE
};

struct shape {
        enum shape_type type;
        union {
                struct {
                        struct vec3d center;
                        double radius;
                } sphere;
        };
};

#endif //XEOM_SHAPE_H
