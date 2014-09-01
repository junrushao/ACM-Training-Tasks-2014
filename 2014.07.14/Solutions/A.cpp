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
#include <sstream>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int pos[1000];

void solve() {
	vector<vector<string> > vec;
	string cur;
	for( ; getline(cin, cur); ) {
		stringstream ss(cur);
		vector<string> tmp;
		for( ; ss >> cur; ) {
			tmp.push_back(cur);
		}
		vec.push_back(tmp);
	}
	int tot = 1;
	int last = 0;
	pos[0] = 0;
	for( ; ; ) {
		int flag = false;
		int maxlen = 0;
		for(int i = 0; i < (int)vec.size(); ++ i) {
			if ((int)vec[i].size() < tot) continue;
			flag = true;
			maxlen = max(maxlen, (int)vec[i][tot - 1].size());
		}
		if (flag == false) break;
		last += maxlen + 1;
		pos[tot ++] = last;
	}
	for(int i = 0; i < (int)vec.size(); ++ i) {
		int last = 0;
		for(int j = 0; j < (int)vec[i].size(); ++ j) {
			for( ; last < pos[j]; ++ last)
				putchar(' ');
			cout << vec[i][j];
			last += vec[i][j].size();
		}
		cout << endl;
	}
}

int main() {
	solve();
	return 0;
}

