#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long sign(long long a, long long b) {
	if (a < b) return 1;
	if (a == b) return 0;
	return -1;
}

int main() {
	long long x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	long long qx1, qx2, qx3, qx4, qy1, qy2, qy3, qy4;
	long long dx, dy, lx, rx, ly, ry;
	qx1 = min(x1, x2), qx2 = max(x1, x2);
	qx3 = min(x3, x4), qx4 = max(x3 ,x4);
	
	lx = max(qx1, qx3), rx = min(qx2, qx4);

	if (lx > rx) {
		printf("0\n");
		return 0;
	}
	dx = rx - lx;

	qy1 = min(y1, y2), qy2 = max(y1, y2);
	qy3 = min(y3, y4), qy4 = max(y3, y4);

	ly = max(qy1, qy3), ry = min(qy2, qy4);

	if (ly > ry) {
		printf("0\n");
		return 0;
	}
	dy = ry - ly;

	long long fx12 = 1, fx34 = 1, fy12 = 1, fy34 = 1;
	fx12 = sign(x1, x2);
	fx34 = sign(x3, x4);
	fy12 = sign(y1, y2);
	fy34 = sign(y3, y4);
	if (fx12 * fy12 == fx34 * fy34) {
		cout << dx + dy << endl;
	} else {
		cout << max(dx, dy) << endl;
	}
	return 0;
}

