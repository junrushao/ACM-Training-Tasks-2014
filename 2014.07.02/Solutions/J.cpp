#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

char ip[55];

long long readIP() {
	scanf("%s", ip);
	long long ret = 0;
	int pos = 0;
	for (int i = 0; i < 4; ++i) {
		int tmp = 0;
		while (ip[pos] >= '0' && ip[pos] <= '9') {
			tmp = tmp * 10 + ip[pos] - '0';
			++pos;
		}
		++pos;
		ret = (ret << 8) | tmp;
	}
	return ret;
}

struct Trie {
	Trie *ch[2];
	long long ret;

	Trie(long long ret = -1) : ret(ret) {
		ch[0] = ch[1] = NULL;
	}

	void insert(long long dest, long long mask, long long dep, long long result) {
		if (dep == 32 || (mask & (1ll << 32 - dep - 1)) == 0) {
			ret = result;
		} else {
			int to = dest >> (32 - dep - 1) & 1;
			if (ch[to] == NULL) {
				ch[to] = new Trie();
			}
			ch[to]->insert(dest, mask, dep + 1, result);
		}
	}
};

Trie *a, *b;

Trie* build() {
	Trie *ret = new Trie();
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		long long dest = readIP(), mask = readIP(), result = readIP();
		dest = dest & mask;
		ret->insert(dest, mask, 0, result);
	}
	return ret;
}

bool go(Trie *a, Trie *b, long long lasta, long long lastb) {
	if (a->ret != -1) {
		lasta = a->ret;
	}
	if (b->ret != -1) {
		lastb = b->ret;
	}
	for (int i = 0; i < 2; ++i) {
		if (a->ch[i] != NULL || b->ch[i] != NULL) {
			if (a->ch[i] == NULL) {
				a->ch[i] = new Trie(a->ret);
			}
			if (b->ch[i] == NULL) {
				b->ch[i] = new Trie(b->ret);
			}
			if (!go(a->ch[i], b->ch[i], lasta, lastb)) {
				return false;
			}
		} else {
			if (lasta != lastb) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	a = build();
	b = build();
	puts(go(a, b, -1, -1) ? "YES" : "NO");
	return 0;
}
