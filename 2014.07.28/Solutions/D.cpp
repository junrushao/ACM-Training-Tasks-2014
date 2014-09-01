#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 11;
const double EPS = 1e-8;
const double PI = acos(-1.0);

int signum(double x) {
    return x < -EPS? -1: x > EPS;
}

inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;

    Point(double x = 0, double y = 0): x(x), y(y) {}
    
    double norm2() const {
        return sqr(x) + sqr(y);
    }

    double norm() const {
        return sqrt(norm2());
    }

};

istream &operator >>(istream &in, Point &p) {
    return in >> p.x >> p.y;
}

Point operator -(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

int n;
double r[N];
Point p[N];

double arcCos(double x) {
    return acos(min(max(x, -1.0), 1.0));
}

double getArea(int i) {
    double a = r[0];
    double b = r[i];
    double d = (p[i] - p[0]).norm();
    double theta = arcCos((sqr(a) + sqr(d) - sqr(b)) / (2 * a * d));
    double alpha = PI - arcCos((sqr(b) + sqr(d) - sqr(a)) / (2 * b * d));
    return sqr(r[1]) * alpha - sqr(r[0]) * theta + a * d * sin(theta);
}

int main() {
    cin >> n;
    for (int i = 0; i <= n; ++ i) {
        cin >> p[i] >> r[i];
    }
    double result = 0;
    for (int mask = 0; mask < (1 << n); ++ mask) {
        bool valid = true;
        for (int i = 1; i <= n; ++ i) {
            if (mask >> (i - 1) & 1) {
                for (int j = i + 1; j <= n; ++ j) {
                    if (mask >> (j - 1) & 1) {
                        valid &= signum((p[i] - p[j]).norm() - r[i] - r[j]) >= 0;
                    }
                }
            }
        }
        if (valid) {
            double area = sqr(r[0]) * PI;
            for (int i = 1; i <= n; ++ i) {
                if (mask >> (i - 1) & 1) {
                    area += getArea(i);
                }
            }
            result = max(result, area);
        }
    }
    printf("%.4f\n", result);
    return 0;
}

