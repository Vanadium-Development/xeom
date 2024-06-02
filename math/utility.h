//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#ifndef XEOM_UTILITY_H
#define XEOM_UTILITY_H

#define rgb(_r, _g, _b) ((struct Pixel) {.r = _r, .g = _g, .b = _b})

/**
 * Returns the number of solutions (0 to 2)
 */
int solve_quadratic(double a, double b, double c, double (*result)[2]);

double min(double d1, double d2);

#endif //XEOM_UTILITY_H
