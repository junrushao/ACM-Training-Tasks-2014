#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)

const int N = 10000 + 10;
const int V = 100 + 10;
const double EPS = 1e-6;

int n;
vector< vector< pair<int, int> > > con[N];
vector<pair<int, int> > vec[N];
map< pair<int, int>, int> freq;
int cnt[V][V], preMax[V][V];
int larger[V][V];

int sign(double x)
{
	return x < -EPS ? -1 : x > EPS;
}

struct Node
{
	double x, y;
	Node() {}
	Node(double x, double y) : x(x), y(y) {}
	int operator < (const Node &that) const {
		int tmp = sign(x - that.x);
		if (tmp) return tmp < 0;
		return sign(y - that.y) < 0;
	}
};

void solve() {
	freq.clear();
	int t, v;
	for(int i = 0; i < n; ++ i) {
		scanf("%d%d", &t, &v);
		freq[make_pair(t, v)] ++;
	}
	for(int i = 0; i < N; ++ i) {
		vec[i].clear();
	}
	int ret = 0;
	foreach(it, freq) {
		vec[it->first.first].push_back(make_pair(it->first.second, it->second));
		ret = max(ret, it->second);
	}
	memset(cnt, 0, sizeof cnt);
	memset(preMax, 0, sizeof preMax);

	int cur = 0;
	for(int t = 10000; t > 0; -- t) {

		{
			int tmp = 0;
			foreach(it, vec[t]) {
				tmp += it->second;
			}
			ret = max(ret, tmp);
		}

		foreach(now, vec[t]) {
			for(int delta = 1; delta <= 100; ++ delta) {
				ret = max(ret, now->second + preMax[(cur + delta) % V][larger[delta][now->first]]);
			}

			foreach(it, con[now->first]) {
				int tmp = now->second;
				foreach(ss, (*it)) {
					tmp += cnt[(cur + ss->first) % V][ss->second];
				}
				ret = max(ret, tmp);
			}
		}

		for(int i = 0; i < V; ++ i) { 
			cnt[cur][i] = 0;
		}
		foreach(it, vec[t]) {
			cnt[cur][it->first] = it->second;
		}
		for(int i = 100; i >= 0; -- i) {
			preMax[cur][i] = max(preMax[cur][i + 1], cnt[cur][i]);
		}
		cur = (cur - 1 + V) % V;
	}
	cout << ret << endl;
}

int main() {
	for(int v = 1; v <= 100; ++ v) {
		map<Node, vector<pair<int, int> > > tmpS;
		for(int t = 1; t <= 100; ++ t) {
			larger[t][v] = 101;
			for(int v2 = v + 1; v2 <= 100; ++ v2) {
				double x = (double)v2 * t / (double)(v2 - v);
				double y = (double)v * v2 * t / (v2 - v);
				if (y > 100 + EPS) continue;
				if (larger[t][v] == 101)
					larger[t][v] = v2;
				tmpS[Node(x, y)].push_back(make_pair(t, v2));
			}
		}
		int cnt = 0;
		foreach(it, tmpS) {
			vector< pair<int, int> > &cur = it->second;
			if (cur.size() <= 1) continue;
			con[v].push_back(cur);
			cnt += cur.size();
		}
	}
	for( ; cin >> n; ) {
		solve();
	}
	return 0;
}