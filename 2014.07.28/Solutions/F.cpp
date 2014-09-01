#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 25;
const int DELTA[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int n, step[N][N][N][N], queue[N * N * N * N];
char map[N][N + 1];

inline bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n && map[x][y] != '#';
}

inline int makeState(int x_1, int y_1, int x_2, int y_2) {
    return (x_1 << 15) | (y_1 << 10) | (x_2 << 5) | y_2;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", map[i]);
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            for (int x = 0; x < n; ++ x) {
                for (int y = 0; y < n; ++ y) {
                    step[i][j][x][y] = INT_MAX;
                }
            }
        }
    }
    int tail = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (map[i][j] == '*') {
                for (int x = 0; x < n; ++ x) {
                    for (int y = 0; y < n; ++ y) {
                        if (map[x][y] != '#' && (x != i || y != j)) {
                            step[x][y][i][j] = 0;
                            queue[tail ++] = makeState(x, y, i, j);
                        }
                    }
                }
            }
        }
    }
    int head = 0;
    while (head != tail) {
        int ret = queue[head ++];
        int x_1 = ret >> 15;
        int y_1 = (ret >> 10) & 31;
        int x_2 = (ret >> 5) & 31;
        int y_2 = ret & 31;
        ret = step[x_1][y_1][x_2][y_2] + 1;
//printf("%d, %d, %d, %d, %d\n", x_1, y_1, x_2, y_2, ret);
        for (int k = 0; k < 4; ++ k) {
            int x_3 = x_1 + DELTA[k][0];
            int y_3 = y_1 + DELTA[k][1];
            if (check(x_3, y_3) && (x_3 != x_2 || y_3 != y_2)) {
                int &reg = step[x_3][y_3][x_2][y_2];
                if (ret < reg) {
                    reg = ret;
                    queue[tail ++] = makeState(x_3, y_3, x_2, y_2);
                }
                if (x_2 + DELTA[k][0] == x_1 && y_2 + DELTA[k][1] == y_1) {
                    int &reg2 = step[x_3][y_3][x_1][y_1];
                    if (ret < reg2) {
                        reg2 = ret;
                        queue[tail ++] = makeState(x_3, y_3, x_1, y_1);
                    }
                }
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            for (int x = 0; x < n; ++ x) {
                for (int y = 0; y < n; ++ y) {
                    if (step[i][j][x][y] < INT_MAX) {
                        result = max(result, step[i][j][x][y]);
                    }
                }
            }
        }
    }
    printf("%d\n", result);
    return 0;
}

