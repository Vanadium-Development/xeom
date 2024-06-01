//
// Created by Piotr Krzysztof Wyrwas on 01.06.24.
//

#ifndef XEOM_UTILITY_H
#define XEOM_UTILITY_H

/**
 * Returns the number of solutions (0 to 2)
 */
int solve_quadratic(double a, double b, double c, double (*result)[2]);

double min(double d1, double d2);

#endif //XEOM_UTILITY_H
