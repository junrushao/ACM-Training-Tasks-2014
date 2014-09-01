#include <climits>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int t;

map<string, int> vari;
map<int, vector<pair<int, pair<char, int> > > > light;

int cnt;

int getvari(const char *s) {
	if (!vari.count(s)) {
		vari[s] = cnt++;
	}
	return vari[s];	
}

const long long INF = 1ll << 60;

int cal(vector<pair<char, int> > cur, long long &lightup) {
	long long ub = -INF, lb = INF;
	int ret = 0;
	for (int i = 0; i < (int)cur.size(); ++i) {
		if (cur[i].first == '<') {
			ub = max(ub, (long long)cur[i].second);
		} else if (cur[i].first == '>') {
			lb = min(lb, (long long)cur[i].second);
		}
	}
	ret += ub != -INF;
	ret += lb != INF;
	if (ub > lb) {
		lightup = min(lightup, 2ll);
	}
	vector<int> tmp;
	for (int i = 0; i < (int)cur.size(); ++i) {
		if (cur[i].first == '=') {
			int t = cur[i].second;
			if (t >= ub && t <= lb) {
				tmp.push_back(t);
			}
		}
	}
	if (tmp.size()) {
		sort(tmp.begin(), tmp.end());
		tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
		ret += tmp.size();
	}
	if (tmp.size() == lb - ub + 1) {
		lightup = min(lightup, (long long)tmp.size() + 2);
	}
	return ret;
}

int n;

int main() {
	while (scanf("%d", &n) == 1 && n) {
		vari.clear();
		light.clear();
		cnt = 0;
		char vv[260], op[2];
		int t1, t2;
		while (n--) {
			scanf("%*s%s%s%d%*s%*s%d%*s", vv, op, &t1, &t2);
			int v = getvari(vv);
			light[t2].push_back(make_pair(v, make_pair(op[0], t1)));
		}
		int ans = 0;	
		for (map<int, vector<pair<int, pair<char, int> > > >::iterator it = light.begin(); it != light.end(); ++it) {
			vector<pair<int, pair<char, int> > > cur = it->second;
			sort(cur.begin(), cur.end());
			long long minlight = INF;
			int sum = 0;
			for (int i = 0; i < (int)cur.size(); ++i) {
				vector<pair<char, int> > tmp;
				int j = i;
				while (j < (int)cur.size() && cur[j].first == cur[i].first) {
					tmp.push_back(cur[j].second);
					++j;
				}
				sum += (int)tmp.size() - cal(tmp, minlight);
				i = j - 1;
			}
			if (minlight != INF) {
				ans += cur.size() - minlight;
			} else {
				ans += sum;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

