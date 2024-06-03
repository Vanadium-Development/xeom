//
// Created by Piotr Krzysztof Wyrwas on 03.06.24.
//

#include "../shader.h"

#include "../../core/rt.h"

ShaderFunction(shader_diffuse, inter, scene, bounces)
{
        bounces ++;

        struct Vec3d normal = shape_normal(inter);
        struct Vec3d intersectionPoint = point_along(inter->ray, inter->distance);

        struct Vec3d randomVector = vec3d_random();

        // Make sure the vector is not pointing at the inside of the sphere
        if (vec3d_dot(&normal, &randomVector) < 0)
                vec3d_mul(&randomVector, -1.0);

        vec3d_normalize(&randomVector);

        struct Ray outboundRay = {.origin = intersectionPoint, randomVector};

        struct Pixel rayColor = _scene_trace_raw(&outboundRay, scene, bounces);

        pixel_mul(&rayColor, 1.0 - inter->shape->shading_hints.diffuse_roughness);

        return rayColor;
}
