//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#ifndef XEOM_RAY_H
#define XEOM_RAY_H

#include "vec3d.h"

struct Ray {
        struct Vec3d origin;
        struct Vec3d direction;
};

struct Vec3d point_along(struct Ray *ray, double distance);

#endif //XEOM_RAY_H
