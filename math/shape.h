//
// Created by Piotr Krzysztof Wyrwas on 28.05.24.
//

#ifndef XEOM_SHAPE_H
#define XEOM_SHAPE_H

#include "vec3d.h"
#include "ray.h"

#include "../shader/shader.h"

enum ShapeType {
        SHAPE_SPHERE,
        SHAPE_POINT_LIGHT
};

struct Shape {
        enum ShapeType type;
        FragmentShader shader;
        struct Pixel color;
        _Bool intersectible;
        struct {
                double diffuse_roughness;
                uint8_t diffuse_samples;
                double metal_fuzz_amount;
        } shading_hints;
        union {
                struct {
                        struct Vec3d center;
                        double radius;
                } sphere;
                struct {
                        struct Vec3d location;
                        double strength;
                } point_light;
        };
};

struct Vec3d shape_normal(struct Intersection *);

double light_intensity(struct Vec3d *point, struct Scene *scene);

struct Intersection {
        _Bool exists;
        struct Ray *ray;
        double distance;
        struct Shape *shape;
};

struct Intersection no_intersection();

struct Intersection ray_shape(struct Ray *ray, struct Shape *shape);

struct Intersection ray_sphere(struct Ray *ray, struct Shape *shape);

#endif //XEOM_SHAPE_H
