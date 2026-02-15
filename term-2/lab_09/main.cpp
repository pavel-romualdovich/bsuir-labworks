#include <iostream>
#include <iomanip>

#include "constants.hpp"
#include "math_functions.hpp"

int main() {
    using namespace std;

    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃    x      ┃    sin^2(x)   ┃      s(x)     ┃" << endl;
    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;

    double step = (B - A) / 10;

    for (double x = A; x < B; x += step) {
        double sin_square= calculate_sin_square(&x);
        double sin_square_taylor = calculate_sin_square_taylor(&x);

        cout << "┃ " << setw(9) << x << " ┃ "
             << setw(13) << calculate_sin_square(&x) << " ┃ "
             << setw(13) << calculate_sin_square_taylor(&x) << " ┃"
             << endl;
    }

    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

    return 0;
}