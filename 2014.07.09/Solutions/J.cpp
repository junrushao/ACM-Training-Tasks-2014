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


#define FOR(i,x) for (__typeof (x.begin ()) i = x.begin (); i != x.end (); ++i)

#define all(x) x.begin (), x.end ()
#define vol(x) (int)x.size ()

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))


using namespace std;


typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

int const N_MAX = 200033;
int const M_MAX = 200033;

struct node {
	int len;
	i64 dp, right;
	node *fa;
	map<char, node*> go;
} base [M_MAX], *top = base, *root;

typedef node *tree;

int N, Ncnt;
char A [N_MAX];
tree Q [M_MAX];

inline tree NewNode (int len) {
	top -> len = len;
	top -> fa = NULL;
	top -> right = 0;
	top -> dp = 0;
	top -> go.clear();
	return top++;
}

inline tree NewNode (int len, tree fa, const map<char, node *> &go) {
	top -> len = len;
	top -> fa = fa;
	top -> right = 0;
	top -> dp = 0;
	top -> go = go;
	return top++;
}

inline void Construct () {
	tree p, q, up, fa;

	N = (int)strlen (A);

	p = root = NewNode (0);

	for (int i = 0; i < N; ++i) {
		char w = A [i];
		up = p;
		p = NewNode (i + 1);
		p -> right = 1;

		for (; up && !up->go.count(w); up = up -> fa) {
			up -> go [w] = p;
		}

		if (!up) {
			p -> fa = root;
		} else {
			q = up -> go [w];
			if (up -> len + 1 == q -> len) {
				p -> fa = q;
			} else {
				fa = NewNode (up -> len + 1, q -> fa, q -> go);
				p -> fa = q -> fa = fa;
				
				for ( ; ; ) {
					if (!up) break;
					tree &tmp = up->go[w];
					if (tmp != q) {
						if (tmp == NULL)
							up->go.erase(w);
						break;
					}
					tmp = fa;
					up = up->fa;
				}
			}
		}
	}
	
	static int cnt [N_MAX];
	
	memset (cnt, 0, sizeof (cnt));
	
	Ncnt = top - base;
	
	for (tree i (base); i != top; ++i) {
		cnt [i -> len] ++;
	}
	
	for (int i = 1; i <= N; ++i) {
		cnt [i] += cnt [i - 1];
	}
	
	for (tree i (base); i != top; ++i) {
		Q [cnt [i -> len]--] = i;
	}
}

inline void get (i64 k) {
	for (int i = Ncnt; i >= 1; --i) {
		tree u = Q [i];
		
		if (u -> fa)
			u -> fa -> right += u -> right;
	}
	root->right = 0;

	for (int i = Ncnt; i >= 1; --i) {
		tree u = Q [i];
		u -> dp = u -> right;

		map<char, tree> &edge = u->go;
		for (map<char, tree>::iterator itr(edge.begin()); itr != edge.end(); ++itr) {
			u->dp += itr->second->dp;
		}
	tree current = root;

	static char buffer[100033];
	int cnt = 0;
	while (true) {
		if (k <= current -> right) {
			break;
		}
		k -= current -> right;

		map<char, tree> &edge = current->go;
		for (map<char, tree>::iterator itr(edge.begin()); itr != edge.end(); ++itr) {
			i64 num = itr->second->dp;
			if (k > num) {
				k -= num;
			} else {
				buffer[cnt++] = itr->first;
				current = itr->second;
				break;
			}
		}
	}
	buffer[cnt] = 0;
	puts (buffer);
}

inline void solve () {
	i64 k; scanf (" %s%I64d", A, &k);

	top = base;
	Construct ();
	get (k);
}


int main () {
	int test; scanf ("%d", &test);
	for (int i = 1; i <= test; ++i) {
		printf ("Case %d: ", i);
		solve ();
	}
	return 0;
}