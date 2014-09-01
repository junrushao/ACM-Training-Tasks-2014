#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define foreach(e,x) for(__typeof(x.begin()) e=x.begin(); e!=x.end(); ++e)

const int N = 100000 + 10;
const int MOD = 1e9 + 7;

void solve()
{
	string s;
	cin >> s;
	set<string> p;
	for(int i = 1; i < s.size(); ++ i) {
		string a, b, ra, rb;
		for(int j = 0; j < i; ++ j) {
			a += s[j];
		}
		for(int j = i; j < s.size(); ++ j) {
			b += s[j];
		}
		ra = a;
		reverse(ra.begin(), ra.end());
		rb = b;
		reverse(rb.begin(), rb.end());
		p.insert(a + b);
		p.insert(b + a);
		p.insert(ra + b);
		p.insert(b + ra);
		p.insert(a + rb);
		p.insert(rb + a);
		p.insert(ra + rb);
		p.insert(rb + ra);
	}
	cout << p.size() << endl;
}

int main()
{
	int test; cin >> test;
	for(int i = 0; i < test; ++ i) {
		solve();
	}
	return 0;
}
