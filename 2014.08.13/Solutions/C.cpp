#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#define foreach(it,e) for (__typeof(e.begin ()) it = e.begin(); it != e.end(); it++)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

int const table[7][7] = 
{
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 4, 2, 5, 3, 0},
	{0, 3, 0, 6, 1, 0, 4},
	{0, 5, 1, 0, 0, 6, 2},
	{0, 2, 6, 0, 0, 1, 5},
	{0, 4, 0, 1, 6, 0, 3},
	{0, 0, 3, 5, 2, 4, 0}
};

struct die {
	int top, front, left;
	inline void calculate_left() {
		left = table[top][front];
	}
	inline int get_front() {
		return front;
	}
	inline int get_back() {
		return 7 - front;
	}
	inline int get_left() {
		return left;
	}
	inline int get_right() {
		return 7 - left;
	}
	inline int get_top() {
		return top;
	}
	inline int get_bottom() {
		return 7 - top;
	}
	inline void rollx(int dir) {
		int _top, _front, _left;
		if (dir == 1) {
			_top = get_back();
			_front = get_top();
			_left = get_left();
		} else {
			_top = get_front();
			_front = get_bottom();
			_left = get_left();
		}
		top = _top;
		front = _front;
		left = _left;
	}
	inline void rolly(int dir) {
		int _top, _front, _left;
		if (dir == 1) {
			_top = get_left();
			_front = get_front();
			_left = get_bottom();
		} else {
			_top = get_right();
			_front = get_front();
			_left = get_top();
		}
		top = _top;
		front = _front;
		left = _left;
	}
};

int const N = 100 + 20;

int n;
int num[N][N], height[N][N];
die dice;

inline void solve() {
	memset(num, 0, sizeof(num));
	memset(height, 0, sizeof(height));
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &dice.top, &dice.front);
		dice.calculate_left();
//cout << dice.get_left() << endl;
		int x = 50, y = 50;
		while (true) {
			bool available = false;
			for (int face = 6; face >= 4; --face) {
				if (dice.get_front() == face) {
					if (height[x + 1][y] < height[x][y]) {
						dice.rollx(1);
						x++;
						available = true;
						break;
					}
				} else if (dice.get_back() == face) {
					if (height[x - 1][y] < height[x][y]) {
						dice.rollx(-1);
						x--;
						available = true;
						break;
					}
				} else if (dice.get_right() == face) {
					if (height[x][y + 1] < height[x][y]) {
						dice.rolly(1);
						y++;
						available = true;
						break;
					}
				} else if (dice.get_left() == face) {
					if (height[x][y - 1] < height[x][y]) {
						dice.rolly(-1);
						y--;
						available = true;
						break;
					}
				}
			}
			if (!available) {
				height[x][y]++;
				num[x][y] = dice.get_top();
				break;
			}
		}
	}
	static int count[7];
	memset(count, 0, sizeof(count));
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < N; ++j) {
			count[num[i][j]]++;
		}
	}
	for (int i = 1; i <= 6; ++i) {
		printf("%d", count[i]);
		if (i < 6) {
			putchar(' ');
		} else {
			putchar('\n');
		}
	}
}

int main () {
	while (scanf("%d", &n) != EOF && n > 0) {
		solve();
	}
	return 0;
}
