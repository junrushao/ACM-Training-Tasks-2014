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

const int N = 1000000 + 10;

int n;
char s[N];
char t[N];

int check()
{
	int sum = 0;
	for(int i = 0; i < n; ++ i) {
		if (t[i] == '(')
			++ sum;
		else
			-- sum;
		if (sum < 0) return false;
	}
	return sum == 0;
}

void solve() {
	scanf("%s", s);
	n = strlen(s);
	if (n & 1) {
		cout << "None" << endl;
		return;
	}
	int a = 0, b = 0;
	vector<int> vec;
	for(int i = 0; i < n; ++ i) {
		if (s[i] == '?') {
			vec.push_back(i);
		} else if (s[i] == '(') {
			++ a;
		} else {
			++ b;
		}
	}
	if (a * 2 > n || b * 2 > n) {
		cout << "None" << endl;
		return;
	}
	int na = n / 2 - a, nb = n / 2 - b;
	int la, fb;
	la = -1; fb = -1;
	for(int i = 0; i < n; ++ i) {
		if (s[i] == '?') {
			if (na) {
				t[i] = '(';
				la = i;
				na --;
			} else {
				t[i] = ')';
				if (fb == -1)
					fb = i;
				nb --;
			}
		} else t[i] = s[i];
	}
	if (! check()) {
		cout << "None" << endl;
		return;
	}
	if (la != -1 && fb != -1) {
		swap(t[la], t[fb]);
		if (check()) {
			cout << "Many" << endl;
			return;
		} 
	}
	cout << "Unique" << endl;
}


int main() {
	solve();
	return 0;
}

