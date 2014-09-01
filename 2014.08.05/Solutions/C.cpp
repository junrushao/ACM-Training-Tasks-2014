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
#include <queue>
#include <set>
#include <map>


#define foreach(i,x) for (__typeof (x.begin ()) i = x.begin (); i != x.end (); ++i)

#define all(x) x.begin (), x.end ()
#define vol(x) (int)x.size ()

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))


using namespace std;


typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;


int const N = 500 + 20;


int n, m, times;
dbl x [N], y [N], z [N];
vector< pair<int, dbl> > adj [N];
int visit [N], prev [N];
dbl dist [N];


inline void dijkstra (int source, int target, vector<int>& list) {
	priority_queue< pair<dbl, int> > heap;
	times++;
	
	for (int i = 1; i <= n; ++i) {
		dist [i] = 1e25;
	}
	
	dist [source] = 0.0;
	heap.push (make_pair (0.0, source));
	
	while (!heap.empty ()) {
		int u = heap.top ().second;
		heap.pop ();
		
		if (visit [u] == times) {
			continue;
		}
		
		visit [u] = times;
		
		foreach (it, adj [u]) {
			int v = it -> first;
			dbl w = it -> second;
			
			if (dist [v] > dist [u] + w) {
				dist [v] = dist [u] + w;
				prev [v] = u;
				
				heap.push (make_pair (-dist [v], v));
			}
		}
	}
	
	list.clear ();
	
	for (int i = target; i != source; i = prev [i]) {
		list.push_back (i);
	}
	
	list.push_back (source);
	
	reverse (all (list));
}


inline dbl get_dist (int i, int j) {
	dbl xx = x [i] - x [j];
	dbl yy = y [i] - y [j];
	dbl zz = z [i] - z [j];
	return sqrt (sqr (xx) + sqr (yy) + sqr (zz));
}


inline void solve () {
	for (int i = 1; i <= n; ++i) {
		adj [i].clear ();
	}
	
	for (int i = 1; i <= n; ++i) {
		scanf ("%lf%lf%lf", z + i, x + i, y + i);
		z [i] *= 5;
	}
	
	for (int i = 1; i <= m; ++i) {
		static char buffer [100];
		int u, v;
		
		scanf ("%d%d%s", &u, &v, buffer);
		
		u++, v++;
		
		dbl distance = get_dist (u, v);
		
		if (buffer [0] == 'w' || buffer [0] == 's') {
			adj [u].push_back (make_pair (v, distance));
			adj [v].push_back (make_pair (u, distance));
		} else if (buffer [0] == 'l') {
			adj [u].push_back (make_pair (v, 1.0));
			adj [v].push_back (make_pair (u, 1.0));
		} else if (buffer [0] == 'e') {
			adj [u].push_back (make_pair (v, 1.0));
			adj [v].push_back (make_pair (u, distance * 3));
		} else {
			assert (false);
		}
	}
	
	int queries;
	scanf ("%d", &queries);
	
	while (queries--) {
		int u, v;
		scanf ("%d%d", &u, &v);
		
		u++, v++;
		
		vector<int> list;
		dijkstra (u, v, list);
		
		for (int i = 0; i < vol (list); ++i) {
			printf ("%d", list [i] - 1);
			
			if (i < vol (list) - 1) {
				putchar (' ');
			} else {
				putchar ('\n');
			}
		}
	}
}


int main () {
	bool first = true;
	while (scanf ("%d%d", &n, &m) != EOF) {
		if (first) {
			first = false;
		} else {
			puts ("");
		}
		solve ();
	}
	return 0;
}
