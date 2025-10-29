#include <cmath>
#include "math_functions.h"

const double EPS = 1e-5;

double get_taylor_cos_cubed(double &x) {
    double taylor_cos_cubed = 0;
    double tmp = 4.0;

    for (int n = 0; abs(tmp) > EPS; n++) {
        taylor_cos_cubed += tmp;

        tmp = -tmp * pow(x, 2) * (3 + pow(9, n + 1))
        / ((2 * n + 1) * (2 * n + 2) * (3 + pow(9, n)));
    }

    return taylor_cos_cubed / 4;
}