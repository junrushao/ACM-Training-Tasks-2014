#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	long long W, H, w, h;
	cin >> W >> H >> w >> h;
	cout << ((W + w) / (w * 2)) * ((H + h) / (h * 2)) << endl;
	return 0;
}

