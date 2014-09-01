#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <complex> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <cassert> 
using namespace std;

struct Bits
{
    unsigned long long low, high;

    Bits() : low(0LLU), high(0LLU) { }

    void andNotWith(int lo, int hi) {
        if (lo < 50)
            low &= ~((1LLU << min(hi,50)) - (1LLU << lo));
        if (hi >= 50)
            high &= ~((1LLU << (hi - 50)) - (1LLU << max(lo - 50, 0)));
    }

    void orWith(int lo, int hi) {
        if (lo < 50)
            low |= (1LLU << min(hi,50)) - (1LLU << lo);
        if (hi >= 50)
            high |= (1LLU << (hi - 50)) - (1LLU << max(lo - 50, 0));
    }

    void xorWith(int lo, int hi) {
        if (lo < 50)
            low ^= (1LLU << min(hi,50)) - (1LLU << lo);
        if (hi >= 50)
            high ^= (1LLU << (hi - 50)) - (1LLU << max(lo - 50, 0));
    }

    bool testBit(int p) const {
        if (p < 50)
            return low >> p & 1;
        return high >> (p - 50) & 1;
    }

};

struct Point {
    int x, y, z;

    Point(int x, int y, int z) : x(x), y(y), z(z) { }
    Point() : x(0), y(0), z(0) { }

    void rotX() {
        z = -z;
        swap(y, z);
    }

    void rotY() {
        x = -x;
        swap(x, z);
    }

    void rotZ() {
        y = -y;
        swap(x, y);
    }

    bool operator<(const Point &o) const {
        return x + y + z < o.x + o.y + o.z;
    }
};

const int maxn = 100;
const int inf = 1000000000;

Bits bits[maxn][maxn];
int n, m;

Point untransform(Point a, Point X, Point Y, Point Z)
{
    int trans[3][6];
    for (int i = 0; i < 3; i++) {
        Point pt = i == 0 ? X : i == 1 ? Y : Z;
        trans[i][0] = pt.x;
        trans[i][1] = pt.y;
        trans[i][2] = pt.z;
        trans[i][3] = trans[i][4] = trans[i][5] = 0;
        trans[i][i + 3] = 1;
    }
    for (int i = 0; i < 3; i++) {
        int pivot = 0;
        for (int j = i; j < 3; j++) 
            if (trans[j][i] != 0)
                pivot = j;
        for (int j = 0; j < 6; j++)
            swap(trans[i][j], trans[pivot][j]);
        if (trans[i][i] < 0) {
            for (int j = 0; j < 6; j++)
                trans[i][j] *= -1;
        }
    }
    int A[3];
    A[0] = a.x;
    A[1] = a.y;
    A[2] = a.z;
    int res[3];
    res[0] = res[1] = res[2] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res[j] += trans[i][j + 3] * A[i];
    for (int i = 0; i < 3; i++) {
        if (res[i] < 0)
            res[i] += n + 1;
    }
    return Point(res[0], res[1], res[2]);
}

const char cubePaint[7][10] = { "..+---+"
                              , "./   /|"
                              , "+---+ |"
                              , "|   | +"
                              , "|   |/."
                              , "+---+.."
};

int getint()
{
    int ret = 0, ch;
    while (!isdigit(ch = getchar()));
    do {
        ret = ret * 10 + ch - '0';
    } while(isdigit(ch = getchar()));
    return ret;
}

bool trans[maxn][maxn][maxn];

char painting[1024][1024];

int main()
{
    char buf[100];
    while (scanf("%d%d", &n, &m) == 2) {
        memset(bits, -1, sizeof(bits));
        Point X(1, 0, 0);
        Point Y(0, 1, 0);
        Point Z(0, 0, 1);
        for (int op = 0; op < m; op++) {
            scanf("%s", buf);
            if (strcmp(buf, "Rotate") == 0) {
                scanf("%s", buf);
                int times = buf[1] == '+' ? 1 : 3;
                for (int it = 0; it < times; ++it)
                    if (buf[0] == 'x') {
                        X.rotX();
                        Y.rotX();
                        Z.rotX();
                    } else if (buf[0] == 'y') {
                        X.rotY();
                        Y.rotY();
                        Z.rotY();
                    } else if (buf[0] == 'z') {
                        X.rotZ();
                        Y.rotZ();
                        Z.rotZ();
                    }
            } else if (strcmp(buf, "Review") == 0) {
                printf("Operation#%d:\n", op+1);
                vector<Point> pts;
                for (int x = 0; x < n; x++)
                    for (int y = 0; y < n; y++)
                        for (int z = 0; z < n; z++) {
                            if (!bits[y][z].testBit(x))
                                continue;
                            int nx = (x + 1) * X.x + (y + 1) * Y.x + (z + 1) * Z.x;
                            int ny = (x + 1) * X.y + (y + 1) * Y.y + (z + 1) * Z.y;
                            int nz = (x + 1) * X.z + (y + 1) * Y.z + (z + 1) * Z.z;
                            if (nx < 0)
                                nx += n + 1;
                            if (ny < 0)
                                ny += n + 1;
                            if (nz < 0)
                                nz += n + 1;
                            nx --;
                            ny --;
                            nz --;
                            pts.push_back(Point(nx, ny, nz));
                        }
                sort(pts.begin(), pts.end());
                memset(painting, '.', sizeof(painting));
                for (int i = 0; i < pts.size(); i++) {
                    int X = 512 + 2 * pts[i].x - 3 * pts[i].z;
                    int Y = 512 - 2 * pts[i].x + 4 * pts[i].y;
                    for (int dx = 0; dx < 6; dx++)
                        for (int dy = 0; dy < 7; dy++) {
                            if (cubePaint[dx][dy] != '.') 
                                painting[X + dx][Y + dy] = cubePaint[dx][dy];
                        }
                }
                int minX = inf, minY = inf;
                int maxX = 0, maxY = 0;
                for (int i = 0; i < 1024; i++)
                    for (int j = 0; j < 1024; j++) {
                        if (painting[i][j] != '.') {
                            minX = min(minX, i);
                            maxX = max(maxX, i);
                            minY = min(minY, j);
                            maxY = max(maxY, j);
                        }
                    }
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) 
                        putchar(painting[x][y]);
                    puts("");
                }
            } else {
                int x1 = getint(), y1 = getint(), x2 = getint(), y2 = getint();
                x1++, y1++, x2++, y2++;
                Point a(1, x1, y1), b(n, x2, y2);
                a = untransform(a, X, Y, Z);
                b = untransform(b, X, Y, Z);
                a.x --, a.y --, a.z --;
                b.x --, b.y --, b.z --;
                if (a.x > b.x)
                    swap(a.x, b.x);
                if (a.y > b.y)
                    swap(a.y, b.y);
                if (a.z > b.z)
                    swap(a.z, b.z);
                if (strcmp(buf, "Remove") == 0) {
                    for (int y = a.y; y <= b.y; y++)
                        for (int z = a.z; z <= b.z; z++)
                            bits[y][z].andNotWith(a.x, b.x + 1);
                } else if (strcmp(buf, "Resume") == 0) {
                    for (int y = a.y; y <= b.y; y++)
                        for (int z = a.z; z <= b.z; z++)
                            bits[y][z].orWith(a.x, b.x + 1);
                } else if (strcmp(buf, "Reverse") == 0) {
                    for (int y = a.y; y <= b.y; y++)
                        for (int z = a.z; z <= b.z; z++)
                            bits[y][z].xorWith(a.x, b.x + 1);
                }
            }
        }
    }
}
