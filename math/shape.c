//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#include "shape.h"

#include "utility.h"

#include <stdbool.h>

#include <stdlib.h>

struct intersection no_intersection()
{
        return (struct intersection) {.exists = false, .shape = NULL, .ray = NULL, .distance = 0.0};
}

struct intersection ray_shape(struct ray *ray, struct shape *shape)
{
        if (shape->type == SHAPE_SPHERE)
                return ray_sphere(ray, shape);

        return no_intersection();
}

struct intersection ray_sphere(struct ray *ray, struct shape *shape)
{
        double Ox = ray->origin.x;
        double Oy = ray->origin.y;
        double Oz = ray->origin.z;

        double Dx = ray->direction.x;
        double Dy = ray->direction.y;
        double Dz = ray->direction.z;

        double Cx = shape->sphere.center.x;
        double Cy = shape->sphere.center.y;
        double Cz = shape->sphere.center.z;

        double r = shape->sphere.radius;

        double a = Dx * Dx + Dy * Dy + Dz * Dz;
        double b = -2 * Cx * Dx - 2 * Cy * Dy - 2 * Cz * Dz + 2 * Ox * Dx + 2 * Oy * Dy + 2 * Oz * Dz;
        double c =
                Cx * Cx - 2 * Cx * Ox + Cy * Cy - 2 * Cy * Oy + Cz * Cz - 2 * Cz * Oz + Ox * Ox + Oy * Oy + Oz * Oz - r * r;

        double solutions[2] = {0.0};

        int solutionCount = solve_quadratic(a, b, c, &solutions);

        if (solutionCount == 0)
                return no_intersection();

        struct intersection inter = {.shape = shape, .ray = ray, .exists = true, .distance = 0.0};

        if (solutionCount == 1)
                inter.distance = solutions[0];
        else
                inter.distance = min(solutions[0], solutions[1]);

        return inter;
}