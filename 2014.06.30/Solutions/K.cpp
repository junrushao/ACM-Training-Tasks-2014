#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
	int n;
	vector<pair<int, int> > a;
	vector<int> l, r;
	cin >> n;
	int x, y;
	for(int i = 0; i < n; ++ i) {
		scanf("%d", &x);
		a.push_back(make_pair(x, i));
	}
	for(int i = 0; i < n; ++ i) {
		scanf("%d%d", &x, &y);
		l.push_back(x);
		r.push_back(y);
	}
	sort(a.begin(), a.end());
	vector<int> match(n, -1);

	for(int i = 0; i < n; ++ i) {
		int p = -1;
		for(int j = 0; j < n; ++ j) {
			if (match[j] < 0 && l[j] <= a[i].first && r[j] >= a[i].first) {
				if (p < 0 || r[p] > r[j]) {
					p = j;
				}
			}
		}
		if (p < 0) {
			cout << "Let's search for another office." << endl;
			return;
		}
		match[p] = i;
	}
	for(int i = 0; i < n; ++ i) {
		for(int j = i + 1; j < n; ++ j) {
			int pi = match[i], pj = match[j];
			if (a[pi].first >= l[j] && a[pi].first <= r[j] && a[pj].first >= l[i] && a[pj].first <= r[i]) {
				cout << "Ask Shiftman for help." << endl;
				return;
			}
		}
	}
	cout << "Perfect!" << endl;
	for(int i = 0; i < n; ++ i) {
		printf("%d", a[match[i]].second + 1);
		if (i + 1 != n) printf(" ");
	}
	cout << endl;
}

int main()
{
	solve();
	return 0;
}
