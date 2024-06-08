//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "../shader.h"
#include "../../core/rt.h"

ShaderFunction(shader_metal, intersection, scene, bounces)
{
        bounces++;

        // First, find the reflection direction and origin point for the new ray
        struct Vec3d normal = shape_normal(intersection);
        struct Vec3d origin = ray_interpolate(intersection->ray, intersection->distance);

        struct Vec3d direction = intersection->ray->direction;
        double scaling = 2 * (vec3d_dot(&intersection->ray->direction, &normal));
        struct Vec3d scaledNormal = normal;
        vec3d_mul(&scaledNormal, scaling);
        vec3d_sub(&direction, &scaledNormal);

        vec3d_normalize(&direction);

        // Trace a ray in that direction
        struct Ray outbound = {
                .origin = origin,
                .direction = direction
        };

        struct Pixel color = _scene_trace_raw(&outbound, scene, bounces);

        pixel_mul(&color, 1.0);

        return color;
}
