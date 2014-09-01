#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <complex>
#include <set>
#include <utility>
#include <vector>

typedef std::complex <double> Point;

const int N = 4;

int x[N], y[N];
Point  c[N];
double r[N];

int square(int x)
{
    return x * x;
}

const double EPS = 1e-9;
const double PI  = acos(-1.);

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

double det(const Point &a, const Point &b)
{
    return a.real() * b.imag() - a.imag() * b.real();
}

std::vector <std::pair <double, int> > events;

void add_event(double a, int d)
{
    events.push_back(std::make_pair(a, d));
}

void add_pair(double a, double b)
{
    if (signum(a - b) <= 0) {
        add_event(a, +1);
        add_event(b, -1);
    } else {
        add_pair(a, +PI);
        add_pair(-PI, b);
    }
}

Point polar(double t)
{
    return Point(cos(t), sin(t));
}

Point raiuds(int i, double t)
{
    return c[i] + polar(t) * r[i];
}

double result[N + 1];

int main()
{
    int tests = 0;
    while (true) {
        bool all_zero = true;
        for (int i = 0; i < 4; ++ i) {
            scanf("%d%d", x + i, y + i);
            all_zero &= x[i] == 0;
            all_zero &= y[i] == 0;
        }
        if (all_zero) {
            break;
        }
        int n = 0;
        std::set <std::pair <std::pair <int, int>, int> > circles;
        for (int i = 0; i < 2; ++ i) {
            for (int j = 2; j < 4; ++ j) {
                if (x[i] != x[j] || y[i] != y[j]) {
                    int ox = x[i] + x[j];
                    int oy = y[i] + y[j];
                    int d2 = square(x[i] - x[j]) + square(y[i] - y[j]);
                    std::pair <std::pair <int, int>, int> circle = std::make_pair(std::make_pair(ox, oy), d2);
                    if (!circles.count(circle)) {
                        circles.insert(circle);
                        c[n] = Point(0.5 * ox, 0.5 * oy);
                        r[n ++] = 0.5 * sqrt((double)d2);
                    }
                }
            }
        }
        memset(result, 0, sizeof(result));
        for (int i = 0; i < n; ++ i) {
            events.clear();
            add_event(-PI, 0);
            add_event(+PI, 0);
            for (int j = 0; j < n; ++ j) {
                if (i != j) {
                    if (signum(std::abs(c[i] - c[j]) - std::abs(r[i] - r[j])) <= 0) {
                        if (signum(r[i] - r[j]) <= 0) {
                            add_pair(-PI, PI);
                        }
                    } else {
                        if (signum(std::abs(c[i] - c[j]) - (r[i] + r[j])) >= 0) {
                            continue;
                        }
                        double d = std::abs(c[j] - c[i]);
                        Point b = (c[j] - c[i]) / d * r[i];
                        double t = acos((r[i] * r[i] + d * d - r[j] * r[j]) / (2 * r[i] * d));
                        Point a = b * polar(-t);
                        Point c = b * polar(+t);
                        add_pair(std::arg(a), std::arg(c));
                    }
                }
            }
            std::sort(events.begin(), events.end());
            int count = events[0].second;
            for (int j = 1; j < (int)events.size(); ++ j) {
                double delta = events[j].first - events[j - 1].first;
                result[count] += r[i] * r[i] * (delta - sin(delta));
                result[count] += det(raiuds(i, events[j - 1].first), raiuds(i, events[j].first));
                count += events[j].second;
            }
        }
        printf("Case %d: %.3f\n\n", ++ tests, 0.5 * (result[0] - result[n - 1]));
    }
    return 0;
}
