#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3 * 100005, N2 = N << 1;

int n;
char s[N];

int sym[N2];

void manacher(char text[], int n, int palindrome[]) {
	palindrome[0] = 1;
	for (int i = 1, j = 0; i < (n << 1) - 1; ++ i) {
		int p = i >> 1;
		int q = i - p;
		int r = (j + 1 >> 1) + palindrome[j] - 1;
		palindrome[i] = r < q ? 0 : min(r - q + 1, palindrome[(j << 1) - i]);
		while (0 <= p - palindrome[i] && q + palindrome[i] < n && text[p - palindrome[i]] == text[q + palindrome[i]]) {
			palindrome[i]++;
		}
		if (q + palindrome[i] - 1 > r) {
			j = i;
		}
	}
}

int a[N];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", s);
		n = strlen(s);
		manacher(s, n, sym);
		for (int i = 0; i < n * 2 - 1; ++i) {
			if (i & 1) {
				a[i >> 1] = sym[i];
			}
		}
		--n;
		vector<pair<int, int> > evt;
		for (int i = 0; i < n; ++i) {
			evt.push_back(make_pair(i + a[i], i));
		}
		int ans = 0;
		sort(evt.begin(), evt.end());
		set<int> tr;
		for (int i = 0, j = 0; i < n; ++i) {
			set<int>::iterator it = tr.lower_bound(2 * i - a[i]);
			if (it != tr.end()) {
				ans = max(ans, i - (*it) / 2);
			}
			tr.insert(2 * i);	
			while (j < (int)evt.size() && evt[j].first == i) {
				tr.erase(2 * evt[j].second);	
				++j;
			}
		}
		printf("%d\n", ans * 4);
	}
	return 0;
}
