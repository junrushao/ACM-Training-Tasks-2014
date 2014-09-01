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


#define foreach(i,x) for (__typeof (x.begin ()) i = x.begin (); i != x.end (); ++i)

#define all(x) x.begin (), x.end ()
#define vol(x) (int)x.size ()

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

#define X first
#define Y second


using namespace std;


typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;


i64 const INF = 1LL << 60;


struct bit {
	int static const N = 1e6 + 10;
	
	int n;
	i64 tree [N];
	
	inline void insert (int x, const i64& v) {
		for (int i = x; i <= n; i += lowbit (i)) {
			tree [i] = max (tree [i], v);
		}
	}
	
	inline i64 get (int x) {
		i64 ans = -INF;
		for (int i = x; i >= 1; i -= lowbit (i)) {
			ans = max (ans, tree [i]);
		}
		return ans;
	}
	
	inline void clear () {
		for (int i = 1; i <= n; ++i) {
			tree [i] = -INF;
		}
	}
};

struct st {
	int static const N = 1e6 + 10;
	
	int n;
	multiset< pair<i64, int> > tree [N];
	
	inline pair<i64, int> get (int x) {
		pair<i64, int> ans = make_pair (INF, 0);
		
		for (int i = x; i <= n; i += lowbit (i)) {
			if (!tree [i].empty ()) {
				ans = min (ans, *tree [i].begin ());
			}
		}
		
		return ans;
	}
	
	inline void insert (int x, const pair<i64, int>& v) {
		for (int i = x; i >= 1; i -= lowbit (i)) {
			tree [i].insert (v);
		}
	}
	
	inline void erase (int x, const i64& y) {
		for (int i = x; i >= 1; i -= lowbit (i)) {
			multiset< pair<i64, int> >::iterator it = tree [i].lower_bound (make_pair (y, 0));
		
			if (it != tree [i].end ()) {
				tree [i].erase (it);
			}
		}
	}
	
	inline void clear () {
		for (int i = 1; i <= n; ++i) {
			tree [i].clear ();
		}
	}
};


int const N = 1e5 + 10;


int n;
int type [N];
pair<i64, i64> cord [N];
vector<i64> vec;

bit bit1, bit2;
st st1, st2;


inline pair<i64, i64> transform1 (const pair<i64, i64>& cord) {
	return make_pair (-cord.Y + cord.X, cord.Y + cord.X);
}

inline pair<i64, i64> transform2 (const pair<i64, i64>& cord) {
	return make_pair (-cord.Y + 2 * cord.X, cord.Y + 2 * cord.X);
}

inline int idx (const i64& num) {
	return lower_bound (all (vec), num) - vec.begin () + 1;
}


inline void solve () {
	scanf ("%d", &n);
	
	for (int i = 1; i <= n; ++i) {
		static char buffer [10];
		int x, y;
		
		scanf ("%d%d%s", &x, &y, buffer);
		
		cord [i].X = x;
		cord [i].Y = y;
		
		if (buffer [0] == 'W') {
			type [i] = 0;
		} else {
			type [i] = 1;
		}
	}
	
	
	vec.clear ();
	
	for (int i = 1; i <= n; ++i) {
		vec.push_back (transform1 (cord [i]).X);
		vec.push_back (transform2 (cord [i]).X);
	}
	
	sort (all (vec));
	vec.erase (unique (all (vec)), vec.end ());
	
	
	bit1.n = bit2.n = st1.n = st2.n = vol (vec) + 2;
	
	bit1.clear (); bit2.clear (); st1.clear (); st2.clear ();
	
	
	int ans = 0;
	
	for (int i = 1; i <= n; ++i) {
		pair<i64, i64> cord1 = transform1 (cord [i]);
		pair<i64, i64> cord2 = transform2 (cord [i]);
		
		if (bit1.get (idx (cord1.X)) >= cord1.Y || bit2.get (idx (cord2.X)) >= cord2.Y) {
			puts ("FAIL");
		} else {
			if (type [i] == 0) {
				bit1.insert (idx (cord1.X), cord1.Y);
				
				while (true) {
					pair<i64, int> ret = st1.get (idx (cord1.X));
					
					i64 min_y = ret.first;
					int id = ret.second;
					
					if (id == 0 || min_y > cord1.Y) {
						break;
					}
					
					ans--;
					
					st1.erase (idx (transform1 (cord [id]).X), transform1 (cord [id]).Y);
					st2.erase (idx (transform2 (cord [id]).X), transform2 (cord [id]).Y);
				}
			} else {
				bit2.insert (idx (cord2.X), cord2.Y);
				
				while (true) {
					pair<i64, int> ret = st2.get (idx (cord2.X));
					
					i64 min_y = ret.first;
					int id = ret.second;
					
					if (id == 0 || min_y > cord2.Y) {
						break;
					}
					
					ans--;
					
					st1.erase (idx (transform1 (cord [id]).X), transform1 (cord [id]).Y);
					st2.erase (idx (transform2 (cord [id]).X), transform2 (cord [id]).Y);
				}
			}
			
			ans++;
			
			st1.insert (idx (cord1.X), make_pair (cord1.Y, i));
			st2.insert (idx (cord2.X), make_pair (cord2.Y, i));
			
			printf ("%d\n", ans);
		}
	}
}


int main () {
	int test; scanf ("%d", &test);
	for (int i = 1; i <= test; ++i) {
		solve ();
	}
	return 0;
}
