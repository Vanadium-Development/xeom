//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_VEC3D_H
#define XEOM_VEC3D_H

struct Vec3d {
        double x;
        double y;
        double z;
};

void vec3d_mul(struct Vec3d *vec, double d);

void vec3d_div(struct Vec3d *vec, double d);

void vec3d_add(struct Vec3d *target, struct Vec3d *another);

void vec3d_sub(struct Vec3d *target, struct Vec3d *another);

double vec3d_magnitude(struct Vec3d *vec);

void vec3d_normalize(struct Vec3d *vec);

double vec3d_dot(struct Vec3d *a, struct Vec3d *b);

struct Vec3d vec3d_random();

#endif //XEOM_VEC3D_H
