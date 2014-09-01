#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int N = 50000;

int position[N + 1], a[N], b[N];
std::vector <int> queries[N];

bool compare(int i, int j)
{
    if (b[i] != b[j]) {
        return b[i] < b[j];
    }
    return i < j;
}

int maximum[N << 1];

int get_id(int l, int r)
{
    return l + r | l != r;
}

void build(int l, int r)
{
    int id = get_id(l, r);
    if (l == r) {
        maximum[id] = -1;
        if (!queries[l].empty()) {
            maximum[id] = b[queries[l].back()];
        }
    } else {
        int m = l + r >> 1;
        build(l,     m);
        build(m + 1, r);
        maximum[id] = std::max(maximum[get_id(l, m)], maximum[get_id(m + 1, r)]);
    }
}

int query(int l, int r, int k)
{
    if (k < l) {
        return -1;
    }
    if (r <= k) {
        return maximum[get_id(l, r)];
    }
    int m = l + r >> 1;
    return std::max(query(l, m, k), query(m + 1, r, k));
}

int update(int l, int r, int k, int a)
{
    int result = -1;
    int id = get_id(l, r);
    if (l == r) {
        result = queries[l].back();
        queries[l].pop_back();
        maximum[id] = -1;
        if (!queries[l].empty()) {
            maximum[id] = b[queries[l].back()];
        }
    } else {
        int m = l + r >> 1;
        if (k <= m || maximum[get_id(l, m)] == a) {
            result = update(l,     m, k, a);
        } else {
            result = update(m + 1, r, k, a);
        }
        maximum[id] = std::max(maximum[get_id(l, m)], maximum[get_id(m + 1, r)]);
    }
    return result;
}

int result[N], ps[N], ps_size;

int main()
{
    int tests;
    scanf("%d", &tests);
    while (tests --) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) {
            int a;
            scanf("%d", &a);
            position[a] = i;
        }
        int q;
        scanf("%d", &q);
        for (int i = 0; i < n; ++ i) {
            queries[i].clear();
        }
        for (int i = 0; i < q; ++ i) {
            scanf("%d%d", a + i, b + i);
            a[i] --, b[i] --;
            queries[a[i]].push_back(i);
        }
        for (int i = 0; i < n; ++ i) {
            std::sort(queries[i].begin(), queries[i].end(), compare);
        }
        build(0, n - 1);
        memset(result, 0, sizeof(result));
        for (int d = n; d >= 1; -- d) {
            ps_size = 0;
            for (int i = d; i <= n; i += d) {
                ps[ps_size ++] = position[i];
            }
            std::sort(ps, ps + ps_size);
            for (int i = 0; i + 1 < ps_size; ++ i) {
                // ps[i], ps[i + 1]
                while (true) {
                    int r = query(0, n - 1, ps[i]);
                    if (r >= ps[i + 1]) {
                        int j = update(0, n - 1, ps[i], r);
                        result[j] = d;
                    } else {
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < q; ++ i) {
            printf("%d\n", result[i]);
        }
    }
    return 0;
}