#include <iostream>
#include <sstream>
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

char buff[100050], bb[100050], s[10050];

int main() {
	ios::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	set<string> a;
	gets(buff);
	while (T--) {
		a.clear();
		gets(buff);
		while (gets(bb) && strcmp(bb, "what does the fox say?") != 0) {
			sscanf(bb, "%*s%*s%s", s);
			a.insert(string(s));
		}
		istringstream ssin(buff);
		string ss;
		bool f = 1;
		while (ssin >> ss) {
			if (a.count(ss)) continue;
			if (!f) cout << ' ' ;
			cout << ss;
			f = false;
		}
		cout << endl;
	}
	return 0;
}
