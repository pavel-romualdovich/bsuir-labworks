#include <cmath>

#include "constants.hpp"

double calculate_sin_square(double *x) {
    double res = pow(sin(*x), 2);
    return res;
}

double calculate_sin_square_taylor(double *x) {
    double sum_part = pow(*x, 2);
    double res = sum_part;
    double n = 1;
    double nominator, denominator;

    while (fabs(sum_part) > EPS) {
        n++;
        nominator = 4 * pow(*x, 2);
        denominator = (2 * n - 1) * (2 * n);
        sum_part = -sum_part * nominator / denominator;
        res += sum_part;
    }

    return res;
}