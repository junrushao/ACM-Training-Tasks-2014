#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#include <bitset>
#include <numeric>

using namespace std;

int main() {
	int T, n, B;
	while (scanf("%d %d %d", &T, &n, &B) == 3 && (T != 0 || n != 0 || B != 0)) {
		vector<pair<double, double> > files;
		for (int index = 0; index < T; ++index) {
			double s;
			int p;
			scanf("%lf %d", &s, &p);
			files.push_back(make_pair(s, s * (100.0 - p) / 100.0));
		}
		sort(files.begin(), files.end());
		priority_queue<double, deque<double>, greater<double> > manager;
		int it = min(n, T);
		for (int index = 0; index < it; ++index) {
			manager.push(files[index].second);
		}
		double ret = 0.0, already = 0.0;
		while (!manager.empty()) {
			double r = manager.top();
			int c = manager.size();
			manager.pop();
			ret += (r - already) / B * c;
			already += r - already;
			if (it < T) {
				manager.push(files[it++].second + already);
			}
		}
		static int task_index = 0;
		printf("Case %d: %.2f\n", ++task_index, ret);
		puts("");
	}
	return 0;
}
