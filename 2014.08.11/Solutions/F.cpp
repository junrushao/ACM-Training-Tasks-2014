#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct Point {
    int x, y;
    
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point rotate() {
        return Point(-y, x);
    }
};

bool operator < (const Point &a, const Point &b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool operator == (const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

inline long long det(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

inline long long calc(const Point &a, const Point &b) {
    return (long long)a.x * a.y - (long long)a.y * b.x * 2 + (long long)b.x * b.y;
}

int n;

const int N = 100005;

Point p[N];
long long ans[N];

long long debug(set<Point> s) {
    long long area = 0;
    for (set<Point>::iterator it = s.begin(); it != s.end(); ++it) {
        cout << it->x << ' ' << it->y << endl;
        set<Point>::iterator it2 = s.upper_bound(*it);
        if (it2 != s.end()) {
            area += calc(*it, *it2);
        }
    }
    return area;
}

set<Point> s;

void solve() {
    s.clear();
    s.insert(p[0]);
    long long area = 0;
    for (int i = 1; i < n; ++i) {
        long long delta = 0;
        Point cur = p[i];
        if (s.size() == 1) {
            Point only = *s.begin();
            if (cur == only || cur.x >= only.x && cur.y < only.y) {
                delta = 0;
            } else if (cur.x <= only.x && cur.y > only.y) {
                delta = 0;
                s.erase(only), s.insert(cur);
            } else {
                s.insert(cur);
                delta = calc(*s.begin(), *s.rbegin());
            }
        } else {
            Point up = *s.rbegin(), left = *s.begin();
            if (up.y == left.y) {
                if (cur.y > up.y) {
                    if (cur.x <= left.x) {
                        delta = -area;
                        s.clear();
                        s.insert(cur);
                    } else {
                        delta -= calc(left, up);
                        s.erase(up);
                        s.insert(cur);
                        delta += calc(left, cur);
                    }
                } else if (cur.y == up.y) {
                    if (left.x <= cur.x && cur.x <= up.x) {
                        delta = 0;
                    } else if (cur.x < left.x) {
                        delta -= calc(left, up);
                        s.erase(left);
                        s.insert(cur);
                        delta += calc(cur, up);
                    } else {
                        delta -= calc(left, up);
                        s.erase(up);
                        s.insert(cur);
                        delta += calc(left, cur);
                    }
                } else if (cur.y < up.y) {
                    if (cur.x < left.x) {
                        s.insert(cur);
                        delta += calc(cur, left);
                    } else {
                        delta = 0;
                    }
                }
            } else {
            if (cur == up || cur == left ||
                cur.x >= up.x && cur.y < up.y ||
                cur.x >= left.x && cur.y <= left.y) {
                delta = 0;
            } else if (cur.x > up.x && cur.y >= up.y) {
                s.insert(cur);
                delta = calc(up, cur);
            } else if (cur.x <= up.x && cur.x > left.x && cur.y > up.y) {
                while (s.rbegin()->x >= cur.x) {
                    Point del = *s.rbegin();
                    s.erase(*s.rbegin());
                    delta -= calc(*s.rbegin(), del);
                }
                delta += calc(*s.rbegin(), cur);
                s.insert(cur);
            } else if (cur.x <= left.x && cur.y > up.y) {
                delta = -area;
                s.clear();
                s.insert(cur);
            } else if (cur.x <= left.x && cur.y == up.y) {
                delta = -area;
                s.clear();
                s.insert(cur);
                s.insert(up);
                delta += calc(cur, up);
            } else if (cur.x <= left.x && cur.y >= left.y) {
                while (s.begin()->y < cur.y) {
                    Point del = *s.begin();
                    s.erase(s.begin());
                    delta -= calc(del, *s.begin());
                }
                delta += calc(cur, *s.begin());
                s.insert(cur);
            } else if (cur.x < left.x && cur.y < left.y) {
                s.insert(cur);
                delta += calc(cur, left);
            } else {
                set<Point>::iterator it = s.lower_bound(Point(cur.x, -INF));
                Point nxt = *it; Point prc = *--it;
                if (prc.y >= cur.y || nxt.x == cur.x && nxt.y >= cur.y) {
                    delta = 0;
                } else {
                    while (true) {
                        set<Point>::iterator it = s.lower_bound(Point(cur.x, -INF));
                        Point nxt = *it;
                        if (nxt.y > cur.y || nxt == up) {
                            Point prc = *--it;
                            delta -= calc(prc, nxt);
                            delta += calc(prc, cur) + calc(cur, nxt);
                            s.insert(cur);
                            break;
                        } else {
                            set<Point>::iterator it2 = it;
                            Point nxtnxt = *++it, prc = *--it2;
                            delta -= calc(prc, nxt) + calc(nxt, nxtnxt);
                            delta += calc(prc, nxtnxt);
                            s.erase(nxt);
                        }
                    }
                }
            }
            }
        }
        area += delta;
        ans[i] += area;
    }
}

void rotate() {
    for (int i = 0; i < n; ++i) {
        p[i] = p[i].rotate();
    }
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i) {
            ans[i] = 0;
            scanf("%d%d", &p[i].x, &p[i].y);
        }
        for (int i = 0; i < 4; ++i) {
            solve();
            rotate();
        }
        for (int i = 0; i < n; ++i) {
            printf("%I64d\n", abs(ans[i]) / 2);
        }
    }
    return 0;
}
