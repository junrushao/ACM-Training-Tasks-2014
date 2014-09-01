#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 16000000;

bool visit[M];

int main() {
    int a, c, m, r;
    scanf("%d%d%d%d", &a, &c, &m, &r);
    memset(visit, 0, sizeof(visit));
    while (!visit[r]) {
        visit[r] = true;
        r = ((long long)a * r + c) % m;
    }
    int result = 0;
    int last = -1;
    for (int i = 0; i < m; ++ i) {
        if (visit[i]) {
            if (last != -1) {
                result = max(result, i - last);
            }
            last = i;
        }
    }
    printf("%d\n", result);
    return 0;
}
