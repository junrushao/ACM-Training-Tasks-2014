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

typedef unsigned long long ULL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 20000 + 10;
const int D = 37;

struct String
{
	int size, id, tooLong;
	vector<int> vec, prefix, suffix, origin;
	void read() {
		scanf("%d", &size);
		if (size == -1) {
			origin.push_back(id);
			return;
		}
		for(int i = 0; i < size; ++ i) {
			int x;
			scanf("%d", &x);
			origin.push_back(x - 1);
		}
	}
	void output() {
		cout << "now is " << id << endl;
		if (tooLong) {
			cout << "too long" << endl;
			for(int i = 0; i < prefix.size(); ++ i) {
				cout << prefix[i] << ' ';
			}
			cout << endl;
			for(int i = 0; i < suffix.size(); ++ i) {
				cout << suffix[i] << ' ';
			}
			cout << endl;
		} else {
			cout << "not too long" << endl;
			for(int i = 0; i < vec.size(); ++ i) {
				cout << vec[i] << ' ';
			}
			cout << endl;
		}
	}
};

int n, m;
String a[N];
int vis[N];
ULL p[N];

void getPrefixAndSuffix(int u)
{
	if (vis[u]) return;
	vis[u] = true;
	if (a[u].size == -1) {
		a[u].tooLong = false;
		a[u].vec.push_back(a[u].id);
		return;
	}

	vector<int> &suffix = a[u].suffix;
	vector<int> &prefix = a[u].prefix;
	int &tooLong = a[u].tooLong;
	tooLong = false;
	for(int i = 0; i < a[u].size; ++ i) {
		int v = a[u].origin[i];
		getPrefixAndSuffix(v);
	}
	for(int i = 0; i < a[u].size; ++ i) {
		int v = a[u].origin[i];
		if (a[v].tooLong) {
			for(int j = 0; j < (int)a[v].prefix.size(); ++ j) {
				prefix.push_back(a[v].prefix[j]);
			}
			tooLong = true;
			break;
		} else {
			for(int j = 0; j < (int)a[v].vec.size(); ++ j) {
				prefix.push_back(a[v].vec[j]);
			}
		}
	}

	tooLong |= ((int)prefix.size() >= (2 * m));
	if (tooLong) {
		suffix.clear();
		for(int i = (int)a[u].origin.size() - 1; i >= 0; -- i) {
			int v = a[u].origin[i];
			if (a[v].tooLong) {
				for(int j = (int)a[v].suffix.size() - 1; j >= 0; -- j) {
					suffix.push_back(a[v].suffix[j]);
				}
				break;
			} else {
				for(int j = (int)a[v].vec.size() - 1; j >= 0; -- j) {
					suffix.push_back(a[v].vec[j]);
				}
			}
		}
		suffix.resize(m);
		reverse(suffix.begin(), suffix.end());
		prefix.resize(m);
	} else {
		vector<int> &vec = a[u].vec;
		vec.clear();
		for(int i = 0; i < (int)a[u].origin.size(); ++ i) {
			int v = a[u].origin[i];
			for(int j = 0; j < (int)a[v].vec.size(); ++ j) {
				vec.push_back(a[v].vec[j]);
			}
		}
	}
}

set<ULL> cnt;

void getSubstring(vector<int> cur)
{
	static ULL pre[N];
	if ((int)cur.size() < m) return;
	pre[0] = 0;
	for(int i = 0; i < (int)cur.size(); ++ i) {
		pre[i + 1] = pre[i] * D + cur[i];
	}
	for(int i = m - 1; i < (int)cur.size(); ++ i) {
		ULL tmp = pre[i + 1] - pre[i - m + 1] * p[m];
		cnt.insert(tmp);
	}
}

void getSubstring(int u)
{
	if (! a[u].tooLong) {
		getSubstring(a[u].vec);
		return;
	}
	vector<int> cur;
	for(int i = 0; i < (int)a[u].origin.size(); ++ i) {
		int v = a[u].origin[i];
		if (a[v].tooLong) {
			for(int j = 0; j < (int)a[v].prefix.size(); ++ j) {
				cur.push_back(a[v].prefix[j]);
			}
			getSubstring(cur);
			cur.clear();
			for(int j = 0; j < (int)a[v].suffix.size(); ++ j) {
				cur.push_back(a[v].suffix[j]);
			}
		} else {
			for(int j = 0; j < (int)a[v].vec.size(); ++ j) {
				cur.push_back(a[v].vec[j]);
			}
		}
	}
	getSubstring(cur);
}

void solve() {
	cin >> n >> m;
	for(int i = 0; i < n; ++ i) {
		a[i].id = i;
		a[i].read();
		vis[i] = false;
	}

	for(int i = 0; i < n; ++ i) {
		getPrefixAndSuffix(i);
		//a[i].output();
	}

	for(int i = 0; i < n; ++ i) {
		getSubstring(i);
	}
	cout << cnt.size() << endl;
}

int main() {
	p[0] = 1;
	for(int i = 1; i < N; ++ i) {
		p[i] = p[i - 1] * D;
	}
	solve();
	return 0;
}
