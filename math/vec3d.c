//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#include "vec3d.h"

#include <math.h>

void vec3d_mul(struct vec3d *vec, double d)
{
        vec->x *= d;
        vec->y *= d;
        vec->z *= d;
}

void vec3d_div(struct vec3d *vec, double d)
{
        vec->x /= d;
        vec->y /= d;
        vec->z /= d;
}

void vec3d_add(struct vec3d *target, struct vec3d *another)
{
        target->x += another->x;
        target->y += another->y;
        target->z += another->z;
}

void vec3d_sub(struct vec3d *target, struct vec3d *another)
{
        target->x -= another->x;
        target->y -= another->y;
        target->z -= another->z;
}

double vec3d_magnitude(struct vec3d *vec)
{
#define SQ(x) ((x)*(x))

        return sqrt(SQ(vec->x) + SQ(vec->y) + SQ(vec->z));

#undef SQ
}

void vec3d_normalize(struct vec3d *vec)
{
        double mag = vec3d_magnitude(vec);

        if (mag == 0.0)
                return;

        vec3d_div(vec, mag);
}

double vec3d_dot(struct vec3d *a, struct vec3d *b)
{
        return a->x * b->x + a->y * b->y + a->z + b->z;
}