#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define mp make_pair
#define pb push_back

using namespace std;

const int mo = 2333333;
const int base = 907;
const int N = 10000005;

int f[N], T, w, n, seed;
vector <pair <int, pair <int, int> > > v;
set <int> s;

inline int find(int i) {
	int ret = i, cur = i;	
	while (f[cur] != cur) {
		cur = f[cur];
	}
	ret = cur;
	while (f[i] != i) {
		cur = f[i];
		f[i] = ret;
		i = cur;
	}
	return ret;
}

void work() {
	long long ans = 0;
	int now = seed;
	v.clear();
	s.clear();
	for (int i = 2; i <= 5 && i <= n; i++) {
		(now *= base) %= mo;
		T = now;
		for (int j = 1; j < i; j++) {
			(now *= base) %= mo;
			w = (T ^ now);
			v.pb(mp(w, mp(i, j)));
		}
	}

	int st = 0, len = 0;
	for (int i = 6; i <= n; i++) {
		(now *= base) %= mo;
		T = now;
		if (s.find(T) != s.end()) {
			st = i;
			break;
		}

		for (int j = i - 5; j < i; j++) {
			(now *= base) %= mo;
			w = (T ^ now);
			v.pb(mp(w, mp(i, j)));
		}

		s.insert(T);
	}

	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}

	if (st != 0) {
		len = st - 6;
	}

	sort(v.begin(), v.end());
	if (n < 100) {
		int ss = 0;
		for (int i = 0; i < (int)v.size(); i++) {
			int a = v[i].second.first, b = v[i].second.second, c = v[i].first;
			if (find(a) != find(b)) {
				f[find(a)] = find(b);
				ans += c;
				ss++;
				if (ss == n - 1) {
					break;
				}
			}

			if (a > 5 && st != 0) {
				int delta = a - b;
				for (int aa = a + len, bb; aa <= n; aa += len) {
					bb = aa - delta;
					if (find(aa) != find(bb)) {
						f[f[aa]] = f[bb];
						ans += c;
					}
				}
			}
		}
	} else {
		long long last = 0, delta;
		for (int n = 5 + len * 4; n <= 5 + len * 5; n += len) {
			for (int i = 1; i <= n; ++i) {
				f[i] = i;
			}
			ans = 0;
			int ss = 0;
			for (int i = 0; i < (int)v.size(); i++) {
				int a = v[i].second.first, b = v[i].second.second, c = v[i].first;
				if (find(a) != find(b)) {
					f[find(a)] = find(b);
					ans += c;
					ss++;
					if (ss == n - 1) {
						break;
					}
				}

				if (a > 5 && st != 0) {
					int delta = a - b;
					for (int aa = a + len, bb; aa <= n; aa += len) {
						bb = aa - delta;
						if (find(aa) != find(bb)) {
							f[f[aa]] = f[bb];
							ans += c;
						}
					}
				}
			}
			if (n == 5 + len * 4) {
				last = ans;
			} else {
				delta = ans - last;
			}
		}
		ans = 0;
		while (n > 100) {
			n -= len;
			ans += delta;
		}
		int ss = 0;
			for (int i = 1; i <= n; ++i) {
				f[i] = i;
			}
		for (int i = 0; i < (int)v.size(); i++) {
			int a = v[i].second.first, b = v[i].second.second, c = v[i].first;
			if (find(a) != find(b)) {
				f[find(a)] = find(b);
				ans += c;
				ss++;
				if (ss == n - 1) {
					break;
				}
			}

			if (a > 5 && st != 0) {
				int delta = a - b;
				for (int aa = a + len, bb; aa <= n; aa += len) {
					bb = aa - delta;
					if (find(aa) != find(bb)) {
						f[f[aa]] = f[bb];
						ans += c;
					}
				}
			}
		}
	}

	cout << ans << endl;
}

int main() {
	while (scanf("%d %d", &n, &seed) == 2 && (n + seed)) {
		work();
	}
	return 0;
}
