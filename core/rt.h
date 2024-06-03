//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#ifndef XEOM_RT_H
#define XEOM_RT_H

#include "../math/vec3d.h"
#include "../math/shape.h"
#include "scene.h"

struct Intersection trace_ray(struct Ray *ray, struct Scene *scene);

struct Ray scene_ray(double x, double y, struct Scene *scene);

struct Pixel _scene_trace(double x, double y, struct Scene *scene);

struct Pixel _scene_trace_raw(struct Ray *ray, struct Scene *scene, uint64_t bounces);

struct Pixel scene_trace_single(double x, double y, struct Scene *scene);

#endif //XEOM_RT_H
