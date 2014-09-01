#include <cstdio>
#include <cstring>
#include <map>
#include <sstream>

const int N = 20000 + 1;

int n, q, parent[N], xorsum[N];
char buffer[47];

int find(int u)
{
    if (parent[u] != u) {
        int p = parent[u];
        parent[u] = find(parent[u]);
        xorsum[u] ^= xorsum[p];
    }
    return parent[u];
}

int main()
{
    int t = 0;
    while (scanf("%d%d", &n, &q) == 2 && n && q) {
        for (int i = 0; i <= n; ++ i) {
            parent[i] = i;
            xorsum[i] = 0;
        }
        printf("Case %d:\n", ++ t);
        bool silent = false;
        int facts = 0;
        while (q --) {
            scanf("%s", buffer);
            if (*buffer == 'I') {
                facts ++;
                fgets(buffer, 47, stdin);
                if (silent) {
                    continue;
                }
                std::istringstream sin(buffer);
                int p, q, v;
                sin >> p >> q;
                if (!(sin >> v)) {
                    v = n;
                    std::swap(q, v);
                }
                if (find(p) == find(q)) {
                    if ((xorsum[p] ^ xorsum[q]) != v) {
                        printf("The first %d facts are conflicting.\n", facts);
                        silent = true;
                    }
                } else {
                    int root = find(p);
                    xorsum[root] = v ^ xorsum[p] ^ xorsum[q];
                    parent[root] = find(q);
                }
            } else if (*buffer == 'Q') {
                int k;
                scanf("%d", &k);
                int result = 0;
                std::map <int, int> unknowns;
                for (int i = 0; i < k; ++ i) {
                    int p;
                    scanf("%d", &p);
                    int root = find(p);
                    result ^= xorsum[p];
                    unknowns[root] ^= 1;
                }
                if (silent) {
                    continue;
                }
                if (unknowns[find(n)]) {
                    result ^= xorsum[n];
                    unknowns[find(n)] = 0;
                }
                bool valid = true;
                for (std::map <int, int>::iterator it = unknowns.begin(); it != unknowns.end(); ++ it) {
                    valid &= !it->second;
                }
                if (valid) {
                    printf("%d\n", result);
                } else {
                    puts("I don't know.");
                }
            }
        }
        puts("");
    }
    return 0;
}
