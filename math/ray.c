//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "ray.h"

struct Vec3d point_along(struct Ray *ray, double distance)
{
        struct Vec3d vec = ray->origin;
        struct Vec3d offset = ray->direction;
        vec3d_mul(&offset, distance);
        vec3d_add(&vec, &offset);
        return vec;
}
