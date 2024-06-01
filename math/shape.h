//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_SHAPE_H
#define XEOM_SHAPE_H

#include "vec3d.h"
#include "ray.h"

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

struct intersection {
        _Bool exists;
        struct ray *ray;
        double distance;
        struct shape *shape;
};

struct intersection no_intersection();

struct intersection ray_shape(struct ray *ray, struct shape *shape);

struct intersection ray_sphere(struct ray *ray, struct shape *shape);

#endif //XEOM_SHAPE_H
