//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#include "utility.h"

#include "math.h"

int solve_quadratic(double a, double b, double c, double (*result)[2])
{
        double discriminant = (b * b) - 4 * a * c;

        // No real results
        if (discriminant < 0)
                return 0;

        (*result)[0] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

        if (discriminant > 0)
                (*result)[1] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
        else
                return 1;

        return 2;
}

double min(double d1, double d2)
{
        return (d1 < d2) ? d1 : d2;
}