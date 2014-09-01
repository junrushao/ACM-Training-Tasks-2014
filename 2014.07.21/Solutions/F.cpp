#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int N = 111111;
const int INF = 100000000;

int a[3][N];
vector<int> values;
int n, m;
int first[3][3 * N], visit[3 * N];

set<pair<int, int> > s;
map<int, int> del;
priority_queue<int> q;

void insert(int a, int b) {
	//printf("insert %d %d\n", a, b);
	pair<int, int> tmp = make_pair(a, b);
	set<pair<int, int> > :: iterator nxt = s.lower_bound(tmp);
	if (nxt->second >= b)
		return ;
	q.push(-(nxt->second + a));
	s.insert(tmp);
	nxt = s.upper_bound(tmp);
	pair<int, int> last = *nxt;
	while(1) {
		set<pair<int, int> > :: iterator it = s.find(tmp);
		--it;
		if (it->second <= b) {
			del[it->first + last.second]++;
			last = *it;
			s.erase(it);
		} else {
			del[it->first + last.second]++;
			q.push(-(it->first + b));
			break;
		}		
	}
}

int getMin() {
	while(1) {
		int x = -q.top();
		if (del[x]) {
			del[x]--;
			q.pop();
			continue;
		}
		return x;
	}
}

void show() {
	for(set<pair<int, int> > :: iterator it = s.begin(); it != s.end(); ++it) {
		printf("%d %d\n", it->first, it->second);
	}
	printf("end----------\n");
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < 3; i++)
		for(int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			values.push_back(a[i][j]);
		}	
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	m = (int)values.size();
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < m; j++) {
			first[i][j] = INF;
		}
		for(int j = n; j >= 1; j--) {
			a[i][j] = lower_bound(values.begin(), values.end(), a[i][j]) - values.begin();
			first[i][a[i][j]] = j;
		}
	}
	
	/*
	for(int i = 0; i < 3; i++, printf("\n"))
		for(int j = 1; j <= n; j++) {
			printf("%d ", a[i][j]);
		}
	
	*/
	fill(visit, visit + m, 0);
	s.insert(make_pair(0, INF + 1));
	s.insert(make_pair(INF + 1, 0));
	q.push(0);
	
	for(int i = 1; i < 3; i++)
		for(int j = 1; j <= n; j++) {
			int key = a[i][j];
			if (first[0][key] == INF && !visit[key]) {
				insert(first[1][key], first[2][key]);
				visit[key] = 1;
			}
		}
	int ans = INF;
	for(int i = n; i >= 1; i--) {
		ans = min(ans, i + getMin());
		//printf("%d   ans = %d\n", getMin(), ans);
		//show();
		if (first[0][a[0][i]] == i) {
			if (first[1][a[0][i]] == INF && first[2][a[0][i]] == INF)
				break;
			insert(first[1][a[0][i]], first[2][a[0][i]]);
		}
		if (i == 1) {
			//show();
			ans = min(ans, getMin());
		}
	}
	printf("%d\n", ans);
	return 0;
}
