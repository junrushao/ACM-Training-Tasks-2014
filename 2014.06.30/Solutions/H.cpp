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
	vector<int> vec(2 * n, 0);
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < n; ++ j) {
			int x;
			scanf("%d", &x);
			if (i < j) {
				for(int k = i; k < j; ++ k) {
					vec[k] += x;
				}
			} else if (i > j) {
				for(int k = j + n; k < i + n; ++ k) {
					vec[k] += x;
				}
			}
		}
	}
	int ret = *max_element(vec.begin(), vec.end());
	if (ret % 36) ret = ret / 36 + 1;
	else ret /= 36;
	cout << ret << endl;
	return 0;
}
