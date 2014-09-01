#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

const int N = 300000 + 10;
const int INF = 1000000000;

int n, m;
int source, destination;
map<string, int> namesToStops, namesToLines;
string stopName[N], lineName[N];
vector<int> route[N];
vector<int> on[N];
char buf[55000000];

void eraseComma(char* c)
{
	for( ; *c; c ++) {
		if (*c == ',' || *c == ' ') *c = 0;
	}
}

void showIt()
{
	cout << n << ' ' << m << endl;
	cout << "show stop" << endl;
	for(int i = 0; i < n; ++ i) {
		cout << stopName[i] << endl;
	}
	cout << "show route" << endl;
	for(int i = 0; i < m; ++ i) {
		cout << lineName[i] << ':' << endl;
		for(int j = 0; j < route[i].size(); ++ j) {
			cout << stopName[route[i][j]] << ' ';
		}
		cout << endl;
	}
}

void inputData()
{
	int tmpLen;

	n = 0;
	namesToStops.clear();
	gets(buf);
	tmpLen = strlen(buf);
	eraseComma(buf);
	for(int i = 1; i < tmpLen; ++ i) {
		if (buf[i] && buf[i - 1] == 0) {
			stopName[n] = buf + i;
			on[n].clear();
			namesToStops[buf + i] = n ++;
		}
	}

	m = 0;
	namesToLines.clear();
	gets(buf);
	tmpLen = strlen(buf);
	eraseComma(buf);
	for(int i = 1; i < tmpLen; ++ i) {
		if (buf[i] && buf[i - 1] == 0) {
			lineName[m] = buf + i;
			route[m].clear();
			namesToLines[buf + i] = m ++;
		}
	}

	for( ; ; ) {
		gets(buf);
		tmpLen = strlen(buf);
		eraseComma(buf);
		int flag = false;
		for(int i = 0; i < tmpLen; ++ i) {
			if (buf[i] == ':') {
				flag = true;
				break;
			}
		}
		if (! flag) break;
		int curLine = namesToLines[buf];
		flag = false;
		for(int i = 0; i < tmpLen; ++ i) {
			if (buf[i] && buf[i - 1] == 0 && flag) {
				route[curLine].push_back(namesToStops[buf + i]);
			}
			if (buf[i] == ':')
				flag = true;
		}
		for(int i = 0; i < (int)route[curLine].size(); ++ i) {
			on[route[curLine][i]].push_back(curLine);
		}
	}

	source = namesToStops[buf + 15];
	gets(buf);
	destination = namesToStops[buf + 18];
	gets(buf);
}

int in[N];
int vis[N];
int trans[N], times[N];

void calcAns()
{
	vector<int> que[2];
	for(int i = 0; i < n; ++ i) {
		in[i] = false;
		times[i] = -INF;
	}
	for(int i = 0; i < m; ++ i) {
		vis[i] = false;
	}
	in[source] = true;
	times[source] = 0;
	trans[source] = 0;
	for(int i = 0; i < (int)on[source].size(); ++ i) {
		que[0].push_back(on[source][i]);
		vis[on[source][i]] = true;
	}
	for(int i = 0; que[i & 1].size(); ++ i) {
		int cur = i & 1;
		que[cur ^ 1].clear();

		for(int j = 0; j < (int)que[cur].size(); ++ j) {
			int curLine = que[cur][j];
			int maxv = -INF;
			for(int k = 0; k < (int)route[curLine].size(); ++ k) {
				int u = route[curLine][k];
				if (in[u]) {
					maxv = max(maxv, times[u] - k);
				} else {
					times[u] = max(times[u], maxv + k);
				}
			}
			maxv = -INF;
			for(int k = (int)route[curLine].size() - 1; k >= 0; -- k) {
				int u = route[curLine][k];
				if (in[u]) {
					maxv = max(maxv, times[u] + k);
				} else {
					times[u] = max(times[u], maxv - k);
				}
			}
		}

		vector<int> newStop;
		for(int j = 0; j < (int)que[cur].size(); ++ j) {
			int curLine = que[cur][j];
			for(int k = 0; k < (int)route[curLine].size(); ++ k) {
				int u = route[curLine][k];
				if (! in[u]) {
					in[u] = true;
					trans[u] = i + 1;
					newStop.push_back(u);
				}
			}
		}
		for(int j = 0; j < (int)newStop.size(); ++ j) {
			int u = newStop[j];
			for(int k = 0; k < (int)on[u].size(); ++ k) {
				int v = on[u][k];
				if (! vis[v]) {
					vis[v] = true;
					que[cur ^ 1].push_back(v);
				}
			}
		}
	}

	if (times[destination] == 1 && trans[destination] == 1) {
		printf("optimal travel from %s to %s: %d line, %d minute\n", stopName[source].c_str(), stopName[destination].c_str(), trans[destination], times[destination]);
	} 
	if (times[destination] == 1 && trans[destination] > 1) {
		printf("optimal travel from %s to %s: %d lines, %d minute\n", stopName[source].c_str(), stopName[destination].c_str(), trans[destination], times[destination]);
	} 
	if (times[destination] > 1 && trans[destination] == 1) {
		printf("optimal travel from %s to %s: %d line, %d minutes\n", stopName[source].c_str(), stopName[destination].c_str(), trans[destination], times[destination]);
	} 
	if (times[destination] > 1 && trans[destination] > 1) {
		printf("optimal travel from %s to %s: %d lines, %d minutes\n", stopName[source].c_str(), stopName[destination].c_str(), trans[destination], times[destination]);
	} 
}

void solve() {
	inputData();
	calcAns();
}

int main() {
	int test;
	cin >> test;
	gets(buf);
	gets(buf);
	for( ; test --; ) {
		solve();
	}
	return 0;
}

