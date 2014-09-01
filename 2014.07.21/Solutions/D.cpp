#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int BAR = 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6;

int fa[BAR]; 
char trans[BAR];

int stamp, vis[BAR];

int qhead, qtail, q[BAR];
short ti[BAR];

int tr[65];

int a[9];

inline int zip() {
	int ret = 0;
	for (int i = 0; i < 9; ++i) {
		ret = ret * 6 + a[i];
	}
	return ret;
}

inline int unzip(int s) {
	for (int i = 8; i >= 0; --i) {
		a[i] = s % 6;
		s /= 6;
	}
}

int succ;

string ans;

int tmp[3];

bool slide(int a[3]) {
	bool ret = false, merge[3] = {0, 0, 0};
	for (int i = 1; i < 3; ++i) {
		if (a[i] == 0) {
			continue;
		}
		for (int j = i - 1; j >= 0; --j) {
			if (a[j] != 0) {
				if (!merge[j] && a[j] == a[j + 1]) {
					ret = true;
					a[j + 1] = 0;
					++a[j];
					merge[j] = true;
					break;
				}
			} else {
				ret = true;
				a[j] = a[j + 1];
				a[j + 1] = 0;
			}
		}
	}
	return ret;
}

void check_succ(int st, char last) {
	for (int i = 0; i < 9; ++i) {
		if (a[i] == 6) {
			ans += last;
			succ = st;
			break;
		}
	}
}

bool up(int st, int &nst) {
	bool move = false;
	unzip(st);
	for (int i = 0; i < 3; ++i) {
		tmp[0] = a[i], tmp[1] = a[i + 3], tmp[2] = a[i + 6];
		move |= slide(tmp);
		a[i] = tmp[0], a[i + 3] = tmp[1], a[i + 6] = tmp[2];
	}
	check_succ(st, 'U');
	nst = zip();
	return move;
}

bool down(int st, int &nst) {
	bool move = false;
	unzip(st);
	for (int i = 0; i < 3; ++i) {
		tmp[0] = a[i + 6], tmp[1] = a[i + 3], tmp[2] = a[i];
		move |= slide(tmp);
		a[i + 6] = tmp[0], a[i + 3] = tmp[1], a[i] = tmp[2];
	}
	check_succ(st, 'D');
	nst = zip();
	return move;
}

bool right(int st, int &nst) {
	bool move = false;
	unzip(st);
	for (int i = 0; i < 3; ++i) {
		tmp[0] = a[i * 3 + 2], tmp[1] = a[i * 3 + 1], tmp[2] = a[i * 3];
		move |= slide(tmp);
		a[i * 3 + 2] = tmp[0], a[i * 3 + 1] = tmp[1], a[i * 3] = tmp[2];
	}
	check_succ(st, 'R');
	nst = zip();
	return move;
}

bool left(int st, int &nst) {
	bool move = false;
	unzip(st);
	for (int i = 0; i < 3; ++i) {
		tmp[0] = a[i * 3], tmp[1] = a[i * 3 + 1], tmp[2] = a[i * 3 + 2];
		move |= slide(tmp);
		a[i * 3] = tmp[0], a[i * 3 + 1] = tmp[1], a[i * 3 + 2] = tmp[2];
	}
	check_succ(st, 'L');
	nst = zip();
	return move;
}

int R1, P, Q;
vector<int> r[11];

int newcell(int st, int t) {
	unzip(st);
	int cnt = 0;
	for (int i = 0; i < 9; ++i) {
		cnt += a[i] == 0;
	}
	int k = r[cnt][t - 2] + 1;
	for (int i = 0; i < 9; ++i) {
		if (a[i] == 0) {
			--k;
		 	if (k == 0) {
				a[i] = 1 + (r[10][t - 2] % 10 == 0);
			}
		}
	}
	return zip();
}

void update(int nst, int st, char dir, int t) {
	nst = newcell(nst, t);
	if (vis[nst] != stamp) {
		vis[nst] = stamp;
		fa[nst] = st;
		trans[nst] = dir;
		ti[qtail] = t;
		q[qtail] = nst;
		++qtail;
	}
}

int main() {
	for (int i = 0; i <= 6; ++i) {
		tr[1 << i] = i;
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &R1, &P, &Q);
		for (int i = 1; i <= 10; ++i) {
			r[i].clear();
			r[i].push_back(R1 % i);
		}
		++stamp;
		for (int i = 0; i < 9; ++i) {
			int t;
			scanf("%d", &t);
			a[i] = tr[t];
		}
		int init = zip();
		qhead = 0, qtail = 0, q[qtail] = init, vis[init] = stamp, ti[qtail] = 1;
		++qtail;
		succ = -1;
		ans = "";
		while (qhead < qtail && succ == -1) {
			int st = q[qhead], t = ti[qhead];
			++qhead;
			if (t == r[1].size()) {
				for (int i = 1; i <= 10; ++i) {
					r[i].push_back((r[i].back() * P + Q) % i);
				}
			}
			int nxt;
			if (down(st, nxt) && succ == -1) {
				update(nxt, st, 'D', t + 1);
			}
			if (succ == -1 && left(st, nxt) && succ == -1) {
				update(nxt, st, 'L', t + 1);
			}
			if (succ == -1 && right(st, nxt) && succ == -1) {
				update(nxt, st, 'R', t + 1);
			}
			if (succ == -1 && up(st, nxt) && succ == -1) {
				update(nxt, st, 'U', t + 1);
			}
		}
		if (succ == -1) {
			printf("Always lose!\n");
		} else {
			while (succ != init) {
				ans += trans[succ];
				succ = fa[succ];
			}
			reverse(ans.begin(), ans.end());
			printf("%s\n", ans.c_str());
		}
	}
	return 0;
}

