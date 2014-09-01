#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Fraction {
    long long a, b;

    Fraction (long long n = 0) {
        a = n, b = 1;
    }

    Fraction (long long a, long long b) : a(a), b(b) {
        clear();
    }

    void clear() {
        long long g = __gcd(abs(a), abs(b));
        if (b < 0) {
            g = -g;
        }
        a /= g, b /= g;
    }

    long double real() const {
        return (long double)a / b;
    }
};

bool operator < (const Fraction &a, const Fraction &b) {
    return a.real() < b.real();
}

struct Point3D {
    long long x, y, z;

    Point3D (long long x = 0, long long y = 0, long long z = 0) : x(x), y(y), z(z) {}

    void in() {
        scanf("%lld%lld%lld", &x, &y, &z);
    }

    long long len2() {
        return x * x + y * y + z * z;
    }
};

Point3D operator - (const Point3D &a, const Point3D &b) {
    return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

long long dot (const Point3D &a, const Point3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3D det (const Point3D &a, const Point3D &b) {
    return Point3D(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

struct Line3D {
    Point3D a, b;

    Line3D (Point3D a = Point3D(0, 0, 0), Point3D b = Point3D(0, 0, 0)) : a(a), b(b) {
    }

    void in() {
        a.in(), b.in();
    }
};

const long long INF = 1ll << 60;

Fraction dis(const Point3D &p, const Line3D &l) {
    Fraction ret(INF);
    ret = min((p - l.a).len2(), (p - l.b).len2());
    if (dot(p - l.b, l.a - l.b) >= 0 && dot(p - l.a, l.b - l.a) >= 0) {
        ret = Fraction(det(p - l.a, l.b - l.a).len2(), (l.b - l.a).len2());
    }
    return ret;
}

inline long long sqr(const long long &x) {
    return x * x;
}

Fraction dis(const Line3D &l0, const Line3D &l1) {
    Point3D dir = det(l0.b - l0.a, l1.b - l1.a);
    return Fraction(sqr(dot(l0.a - l1.a, dir)), dir.len2());
}

bool parallel(const Line3D &l0, const Line3D &l1) {
    return det(l0.b - l0.a, l1.b - l1.a).len2() == 0;
}

struct Plane {
    Point3D a, b, c;

    Plane (Point3D a, Point3D b, Point3D c) : a(a), b(b), c(c) {}

    Point3D pvec() const {
        return det(b - a, c - a);
    }
};

inline int sign(const long long &x) {
    return x < 0 ? -1 : x > 0;
}

int side(const Plane &a, const Point3D &p) {
    return sign(dot(a.pvec(), p - a.a));
}

bool cross(const Line3D &l0, const Line3D &l1) {
    Point3D dir = det(l0.b - l0.a, l1.b - l1.a);
    Plane p(l0.a, l0.b, l0.a - dir);
    return side(p, l1.a) * side(p, l1.b) != 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        Line3D l0, l1;    
        l0.in(), l1.in();
        Fraction ans(INF);
        ans = min(ans, min(dis(l0.a, l1), dis(l0.b, l1)));
        ans = min(ans, min(dis(l1.a, l0), dis(l1.b, l0)));
        if (!parallel(l0, l1) && cross(l0, l1) && cross(l1, l0)) {
            ans = min(ans, dis(l0, l1));
        }
        printf("%lld %lld\n", ans.a, ans.b);
    }
    return 0;
}

