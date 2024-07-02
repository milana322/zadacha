#include "functions.h"
#include <cmath>
#include <QStringList>

QVector<int> Functions::checkPrimary(int num) {
    QVector<int> res;
    bool isPrime = true;
    for (int i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) {
            isPrime = false;
            break;
        }
    }
    if (isPrime) {
        return res;
    } else {
        for (int i = 2; i <= num; ++i) {
            while (num % i == 0) {
                res.push_back(i);
                num /= i;
            }
        }
        return res;
    }
}

double Functions::factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    double result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

double Functions::Sin(float x, double epsilon) {
    x = fmod(x, 2 * M_PI); // Преобразование угла в диапазон [0, 2π]
    double sinx = 0;
    double term;
    int i = 0;
    do {
        term = (std::pow(-1, i) * std::pow(x, 2 * i + 1)) / factorial(2 * i + 1);
        sinx += term;
        i++;
    } while (std::fabs(term) > epsilon && i < 100);  // ограничение 100 итерациями для предотвращения бесконечного цикла

    // Округление результата до нужного количества знаков после запятой
    int precision = 0;
    while (epsilon < 1) {
        epsilon *= 10;
        precision++;
    }
    double scale = std::pow(10, precision);
    sinx = std::round(sinx * scale) / scale;

    return sinx;
}
QVector<double> Functions:: solveQuadratic(double A, double B, double C) {
    QVector<double> roots;
    double discriminant = B * B - 4 * A * C;

    if (discriminant > 0) {
        double root1 = (-B + sqrt(discriminant)) / (2 * A);
        double root2 = (-B - sqrt(discriminant)) / (2 * A);
        roots.push_back(root1);
        roots.push_back(root2);
    } else if (discriminant == 0) {
        double root = -B / (2 * A);
        roots.push_back(root);
        roots.push_back(root);
    } else if (discriminant < 0) {
        roots.push_back(0);
        roots.push_back(0);
    }

    return roots;
}

