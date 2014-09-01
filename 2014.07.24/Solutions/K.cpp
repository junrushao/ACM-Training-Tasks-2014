#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct node {
	int x, y;
} d;
void up(int l) {
	for (int i = 1; i <= l; i++) {
		printf("%d %d\n", d.x, d.y);
		d.x++;
	}
	return;
}
void down(int l) {
	for (int i = 1; i <= l; i++) {
		printf("%d %d\n", d.x, d.y);
		d.x--;
	}
	return;
}
void right(int l) {
	for (int i = 1; i <= l; i++) {
		printf("%d %d\n", d.x, d.y);
		d.y++;
	}
	return;
}
void left(int l) {
	for (int i = 1; i <= l; i++) {
		printf("%d %d\n", d.x, d.y);
		d.y--;
	}
	return;
}
int main() {
	int n, l;
	scanf("%d%d", &n, &l);
	if (l & 1 || l > n * n) {
		printf("Unsuitable device\n");
		return 0;
	}
	printf("Overwhelming power of magic\n");
	d.x = 1, d.y = 1;
	if (l <= 4 * n - 4) {
		if (l <= 2 * n) {
			up((l >> 1) - 1);
			right(1);
			down((l >> 1) - 1);
			left(1);
		} else {
			int t = (l - 2 * n) / 2;
			up(n - 1);
			right(t + 1);
			down(n - 1);
			left(t + 1);
		}
	} else if (!(n & 1) ) {
		int t = l - (4 * n - 4);
		up(n - 1);
		right(n - 1);
		down(n - 1);
		for (int i = n - 1; i >= 3; i -= 2) {
			int s = min(t, 2 * n - 4);
			if (s == 0) {
				left(i);
				return 0;
			}
			t -= s;
			s /= 2;
			left(1);
			up(s);
			left(1);
			down(s);
		}
		left(1);
	} else {
		int t = l - (4 * n - 4);
		up(n - 1);
		right(n - 1);
		down(n - 1);
		for (int i = n - 1; i > 4; i -= 2) {
			int s = min(t, 2 * n - 4);
			if (s == 0) {
				left(i);
				return 0;
			}
			t -= s;
			s /= 2;
			left(1);
			up(s);
			left(1);
			down(s);
		}
		if (t == 0) {
			left(d.y - 1);
			return 0;
		}
		if (t <= 2 * n - 4) {
			left(1);
			up(t / 2);
			left(2);
			down(t / 2);
			left(1);
			return 0;
		}
		left(1);
		up(n - 2);
		left(2);
		t -= (2 * n - 4);
		for (int i = n - 2; i >= 3; i -= 2) {
			int s = min(t, 2);
			if (s == 0) {
				down(d.x - 1);
				left(d.y - 1);
				return 0;
			}
			t -= s;
			s /= 2;
			down(1);
			right(s);
			down(1);
			left(s);
		}
		if (t == 0) {
			down(d.x - 1);
			left(d.y - 1);
			return 0;
		}
	}
	return 0;
}
