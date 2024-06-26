//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#include "shape.h"

#include "utility.h"

#include <stdbool.h>

#include <stdlib.h>

struct Vec3d shape_normal(struct Intersection *inter)
{
        if (inter->shape->type != SHAPE_SPHERE)
                return vec(0.0, 0.0, 0.0);

        struct Vec3d normal = ray_interpolate(inter->ray, inter->distance);
        vec3d_sub(&normal, &inter->shape->sphere.center);
        vec3d_normalize(&normal);

        return normal;
}

_Bool _any_obstructions_to(struct Vec3d *origin, struct Vec3d *target, struct Scene *scene)
{
        double distance = vec3d_distance_between(origin, target);
        struct Vec3d d = *target;
        vec3d_sub(&d, origin);
        struct Ray ray = {.origin = *origin, .direction = d};

        for (uint64_t i = 0; i < scene->shapes.length; i++) {
                struct Shape *s = ((struct Shape *) array_get(&scene->shapes, i));
                if (ray_shape(&ray, s).exists)
                        return true;
        }

        return false;
}

#include <stdio.h>

double light_intensity(struct Vec3d *point, struct Scene *scene)
{
        double totalIntensity = 0.0;
        uint64_t sourceCount = 0;
        for (uint64_t i = 0; i < scene->shapes.length; i++) {
                struct Shape *s = ((struct Shape *) array_get(&scene->shapes, i));
                if (s->type != SHAPE_POINT_LIGHT)
                        continue;
                if (_any_obstructions_to(point, &s->point_light.location, scene))
                        continue;
                double distance = vec3d_distance_between(point, &s->point_light.location);

#define CLAMP(x, low, high) (((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))

                totalIntensity += CLAMP((1.0 - (1.0 / s->point_light.strength) * distance), 0.0, 1.0);

                if (totalIntensity > 0.0)
                        sourceCount++;

#undef CLAMP
        }

        if (!sourceCount)
                return 0.0;

        double intensity = totalIntensity / (double) sourceCount;

        if (intensity > 1.0)
                printf("What the fuck?\n");

        return intensity;
}

struct Intersection no_intersection()
{
        return (struct Intersection) {.exists = false, .shape = NULL, .ray = NULL, .distance = 0.0};
}

struct Intersection ray_shape(struct Ray *ray, struct Shape *shape)
{
        if (shape->intersectible)
                return no_intersection();

        if (shape->type == SHAPE_SPHERE)
                return ray_sphere(ray, shape);

        return no_intersection();
}

#define EPSILON (10E-10)

struct Intersection ray_sphere(struct Ray *ray, struct Shape *shape)
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
                Cx * Cx - 2 * Cx * Ox + Cy * Cy - 2 * Cy * Oy + Cz * Cz - 2 * Cz * Oz + Ox * Ox + Oy * Oy + Oz * Oz -
                r * r;

        double solutions[] = {0.0, 0.0};

        int solutionCount = solve_quadratic(a, b, c, &solutions);

        if (solutionCount == 0)
                return no_intersection();

        struct Intersection inter = {.shape = shape, .ray = ray, .exists = true, .distance = 0.0};

        if (solutionCount == 1)
                inter.distance = solutions[0];
        else {
                if (solutions[0] <= EPSILON)
                        inter.distance = solutions[1];
                else if (solutions[1] <= EPSILON)
                        inter.distance = solutions[0];
                else
                        inter.distance = min(solutions[0], solutions[1]);
        }

        if (inter.distance < EPSILON)
                return no_intersection();

        return inter;
}

#undef EPSILON