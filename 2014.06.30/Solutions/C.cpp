#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> a;
	int x, sum = 0;
	for(int i = 0; i < n; ++ i) {
		cin >> x;
		a.push_back(x);
		sum += x;
	}
	vector<int> ret(n, 0);
	int cnt = 0;
	int total = 0;
	for(int i = 0; i < n; ++ i) {
		if (a[i] * (n + 1) > sum) {
			total += a[i] * (n + 1) - sum;
		}
	}
	for(int i = 0; i < n; ++ i) {
		if (a[i] * (n + 1) > sum) {
			ret[i] = 100 * (a[i] * (n + 1) - sum) / total;
		}
		cout << ret[i];
		if (i + 1 != n) cout << ' ';
	}
	cout << endl;
	return 0;
}
