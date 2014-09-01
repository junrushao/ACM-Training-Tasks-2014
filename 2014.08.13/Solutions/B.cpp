#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#define foreach(it,e) for (__typeof(e.begin ()) it = e.begin(); it != e.end(); it++)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

string a;
int l;
int occur[10000000];

inline int to_int(const string& str) {
	int num = 0;
	for (int i = 0; i < (int)str.length(); ++i) {
		num = num * 10 + str[i] - '0';
	}
	return num;
}

inline string to_string(int num) {
	if (num == 0) {
		return "0";
	}
	string str = "";
	for (int i = num; i > 0; i /= 10) {
		char ch = '0' + (i % 10);
		str = ch + str;
	}
	return str;
}

inline void solve() {
	memset(occur, 0xFF, sizeof(occur));
	for (int repeat = 0; repeat <= 20; ++repeat) {
		if (occur[to_int(a)] >= 0) {
			cout << occur[to_int(a)] << " " << a << " " << repeat - occur[to_int(a)] << endl;
			break;
		} else {
			occur[to_int(a)] = repeat;
			while (a.length() < l) {
				a = "0" + a;
			}
			sort(a.begin(), a.end());
			string b = a;
			reverse(b.begin(), b.end());
			a = to_string(to_int(b) - to_int(a));
		}
	}
}

int main () {
	while (cin >> a >> l && l > 0) {
		solve();
	}
	return 0;
}
