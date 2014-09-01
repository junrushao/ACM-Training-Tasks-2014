#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int N = 100005;

int n, tot, b[N << 2];
int hashCnt, hashNow[N];
pair <int, int> a[N];
set <pair <pair <int, int>, int> > s1[N << 2], s2[N << 2], s3[N << 2], s4[N << 2];

int getID(const int &x) {
	return lower_bound(b + 1, b + tot + 1, x) - b;
}

void work(set <pair <pair <int, int>, int> > &s, pair <pair <int, int>, int> a, int now) {
	set <pair <pair <int, int>, int> > :: iterator it;
	while (1) {
		it = s.upper_bound(a);
		if (it == s.end()) {
			break;
		}

		if (it->second >= now) {
			break;
		} else {
			s.erase(it);
		}
	}

	if (it != s.end()) {
		hashNow[it->second] = hashCnt;
	}

	int flag = -1;
	while (1) {
		it = s.upper_bound(a);
		if (it == s.begin()) {
			break;
		} else {
			it--;
		}

		if (it->second >= now) {
			flag = it->second;
			break;
		} else {
			s.erase(it);
		}
	}

	if (flag != -1) {
		hashNow[flag] = hashCnt;
	}
}

int main() {
	scanf("%d", &n);
	b[++tot] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].first, &a[i].second);
		b[++tot] = a[i].first;
		b[++tot] = a[i].second;
		b[++tot] = a[i].first + a[i].second;
		b[++tot] = a[i].first - a[i].second;
	}
	
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		int x = a[i].first, y = a[i].second;
		pair <pair <int, int>, int> now = make_pair(a[i], i);
		s1[getID(x)].insert(now);
		s2[getID(y)].insert(now);
		s3[getID(x + y)].insert(now);
		s4[getID(x - y)].insert(now);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int x = a[i - 1].first, y = a[i - 1].second;
		pair <pair <int, int>, int> now = make_pair(a[i - 1], i - 1);
		hashCnt++;
		work(s1[getID(x)], now, i);
		work(s2[getID(y)], now, i);
		work(s3[getID(x + y)], now, i);
		work(s4[getID(x - y)], now, i);
		if (hashNow[i] != hashCnt) {
			break;
		}

		ans++;
	}

	printf("%d\n", ans);
	return 0;
}

