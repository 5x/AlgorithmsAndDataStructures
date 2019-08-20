#include <iostream>
#include <iomanip>

namespace Solution {

    const double PI = 3.14159265358979323846;

    double pow_(double num, int power) {
        return (power == 0) ? 1 : num * pow_(num, power - 1);
    }

    double pow(double num, int power) {
        return (power < 0) ? 1 / pow_(num, -power) : pow_(num, power);
    }

    double factorial(double n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }

    double cos_(double x, int n, int max) {
        const double value = pow(-1, n) / factorial(2 * n) * pow(x, 2 * n);
        return (n >= max) ? value : value + cos_(x, ++n, max);
    }

    double cos(double x, int n) {
        return cos_(x, 0, n);
    }

    double result(double x, int n) {
        return cos(1 / (x + 1) + PI / 4, n);
    }

}


int main() {
    const int PRECISION = 8;
    double x;

    std::cout << std::setprecision(PRECISION) << "x=";
    while (!(std::cin >> x)) {
        std::cout << "Invalid value, try again.\nx=";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }

    const double y = Solution::result(x, PRECISION);
    std::cout << "y(" << x << ")=" << y << std::endl;

    system("pause");

    return 0;
}
