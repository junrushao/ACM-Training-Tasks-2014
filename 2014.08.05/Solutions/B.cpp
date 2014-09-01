#include<cctype>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
struct Edge {
	int y, f, next;
} edge[33333];
int infi(2e9);
int dis[333], cl, v, q[333], maxflow, n, m, be[333], ed[333], cnt[333], x, l, idx[333];
void build(int x, int y, int f) {
	edge[++l].y = y;
	edge[l].f = f;
	edge[l].next = idx[x];
	idx[x] = l;
}
void cnnt(int x, int y, int f) {
	build(x, y, f);
	build(y, x, 0);
}
bool bfs() {
	fill(dis + 1, dis + 1 + 2 * n + 2, infi);
	dis[q[cl = 1] = 1] = 0;
	for(int op = 1; op <= cl; op++)
		for(int p = idx[v = q[op]]; p; p = edge[p].next)
			if(edge[p].f and dis[edge[p].y] == infi)
				dis[q[++cl] = edge[p].y] = dis[v] + 1;
	return dis[2 * n + 2] != infi;
}
int dfs(int v, int flow) {
	if(v == 2 * n + 2)
		return flow;
	int flow1 = flow, flow2;
	for(int p = idx[v]; p and flow; p = edge[p].next)
		if(dis[edge[p].y] == dis[v] + 1 and edge[p].f) {
			flow2 = dfs(edge[p].y, min(edge[p].f, flow));
			flow -= flow2;
			edge[p].f -= flow2;
			edge[p ^ 1].f += flow2;
		}
	return flow1 - flow;
}
int main() {
	int tst;
	scanf("%d", &tst);
	for(int qq = 1; qq <= tst; qq++) {
		scanf("%d%d", &n, &m);
		maxflow = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d%d%d", &be[i], &ed[i], &cnt[i]);
			cnt[i] = (cnt[i] + m - 1) / m;
			maxflow += cnt[i];
		}
		l = 1;
		fill(idx + 1, idx + 2 * n + 3, 0);
		for(int i = 1; i <= n; i++) {
			cnnt(1, i + 1, cnt[i]);
			cnnt(i + 1 + n, 2 * n + 2, cnt[i]);
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &x);
				if(ed[i] + x < be[j]) {
					cnnt(i + 1, j + 1 + n, infi);
				}
			}
		}
		while(bfs()) {
			maxflow -= dfs(1, infi);
		}
		printf("Case %d: %d\n", qq, maxflow);
	}
	return 0;
}
