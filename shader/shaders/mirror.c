//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "../shader.h"
#include "../../core/rt.h"

ShaderFunction(shader_metal, intersection, scene, bounces)
{
        // First, find the reflection direction and origin point for the new ray
        struct Vec3d orgNormal = shape_normal(intersection);
        struct Vec3d origin = point_along(intersection->ray, intersection->distance);

        uint64_t r = 0;
        uint64_t g = 0;
        uint64_t b = 0;
        uint64_t n = 3;

        for (uint64_t i = 0; i < n; i++) {
                struct Vec3d normal = orgNormal;
                normal.x += (0.1 / (double) RAND_MAX) * (double) rand();
                normal.y += (0.1 / (double) RAND_MAX) * (double) rand();

                // Trace a ray in that direction
                struct Ray outbound = {.origin = origin, .direction = normal};

                struct Pixel color = _scene_trace_raw(&outbound, scene, bounces);

                r += color.r;
                g += color.g;
                b += color.b;
        }

        r /= n;
        g /= n;
        b /= n;

        r /= 1.1;
        g /= 1.1;
        b /= 1.1;

        return rgb(r, g, b);
}
