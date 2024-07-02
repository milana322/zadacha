#pragma once
#include <QVector>
#include <QString>

class Functions {
public:
    QVector<int> checkPrimary(int num);
    double factorial(int n);
    double Sin(float x, double epsilon);
    QVector <double> solveQuadratic(double a, double b, double c);
};
