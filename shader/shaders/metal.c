//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "../shader.h"
#include "../../core/rt.h"

ShaderFunction(shader_metal, intersection, scene, bounces)
{
        bounces++;

        if (bounces + 1 > scene->bounces_limit) {
                intersection->shape->shading_hints.diffuse_roughness = 0.5;
                intersection->shape->color = rgb(255, 255, 255);
                return shader_diffuse(intersection, scene, bounces - 20);
        }

        // First, find the reflection direction and reflectedOrigin point for the new ray
        struct Vec3d normal = shape_normal(intersection);
        struct Vec3d reflectedOrigin = ray_interpolate(intersection->ray, intersection->distance);

        vec3d_normalize(&intersection->ray->direction);
        vec3d_normalize(&normal);

        struct Vec3d direction = intersection->ray->direction;
        vec3d_mul(&direction, -1.0);
        double dotProduct = 2 * vec3d_dot(&direction, &normal);
        struct Vec3d multipliedNormal = normal;
        vec3d_mul(&multipliedNormal, dotProduct);
        vec3d_sub(&direction, &multipliedNormal);

        // Add some fuzz ("roughness") to the metal
        struct Vec3d fuzzVector = vec3d_random();
        vec3d_mul(&fuzzVector, intersection->shape->shading_hints.metal_fuzz_amount);
        vec3d_add(&direction, &fuzzVector);

//        if (vec3d_dot(&direction, &normal) < 0)
//                vec3d_mul(&direction, -1.0);

        // Trace a ray in that direction
        struct Ray outbound = {
                .origin = reflectedOrigin,
                .direction = direction
        };

        struct Pixel color = _scene_trace_raw(&outbound, scene, bounces);

        return color;
}
