#include <iostream>
#include <cmath>

int main() {
    using namespace std;

    double x, y, z;

    cout << "Введите x: ";
    cin >> x;
    cout << "Введите y: ";
    cin >> y;
    cout << "Введите z: ";
    cin >> z;

    double numerator = pow(y + pow(x - 1, 1. / 3.), 1. / 4.);
    double denominator_one = fabs(x - y);
    double denominator_two = pow(sin(z), 2) + tan(z);
    double answer = numerator / (denominator_one * denominator_two);

    cout << "Значение выражения: " << answer << endl;

    return 0;
}