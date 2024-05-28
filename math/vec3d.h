//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_VEC3D_H
#define XEOM_VEC3D_H

struct vec3d {
        double x;
        double y;
        double z;
};

void vec3d_mul(struct vec3d *vec, double d);

void vec3d_div(struct vec3d *vec, double d);

void vec3d_add(struct vec3d *target, struct vec3d *another);

void vec3d_sub(struct vec3d *target, struct vec3d *another);

double vec3d_magnitude(struct vec3d *vec);

void vec3d_normalize(struct vec3d *vec);

double vec3d_dot(struct vec3d *a, struct vec3d *b);

#endif //XEOM_VEC3D_H
