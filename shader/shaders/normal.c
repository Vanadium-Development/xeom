//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "../shader.h"

ShaderFunction(shader_normal, inter, scene, bounces)
{
        struct Vec3d normal = shape_normal(inter);

        double r = 255 * (normal.x + 1.0) / 2.0;
        double g = 255 * (normal.y + 1.0) / 2.0;
        double b = 255 * (normal.z + 1.0) / 2.0;

        return rgb(r, g, b);
}
