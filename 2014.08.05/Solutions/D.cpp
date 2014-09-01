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


using namespace std;


typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;


int const N = 1000 + 20;
u64 const M = 1e9 + 7;


int n, limit, times;
string str [2];

int visit [N][2];
bool ans [N][2];
string start [N], end [N];

inline string mergy (const string& a, const string& b) {
	if ((int)a.length () + (int)b.length () <= limit) {
		return a + b;
	}
	string c;
	for (int i = 0; i < (int)a.length (); ++i) {
		if ((int)c.length () == limit) {
			return c;
		}
		
		c += a [i];
	}
	
	for (int i = 0; i < (int)b.length (); ++i) {
		if ((int)c.length () == limit) {
			return c;
		}
		
		c += b [i];
	}
	
	return c;
}


inline string reverse (const string& x) {
	string y;
	
	for (int i = (int)x.length () - 1; i >= 0; --i) {
		y += x [i];
	}
	
	return y;
}


inline string flip (const string& x) {
	string y;
	
	for (int i = 0; i < (int)x.length (); ++i) {
		y += (x [i] == 'L') ? 'R' : 'L';
	}
	
	return y;
}


inline bool dfs (int n, int idx) {
	if (visit [n][idx] == times) {
		return ans [n][idx];
	}
	
	visit [n][idx] = times;
	bool& result = ans [n][idx];
	
	
	const string& curr = str [idx];
	
	
	if (n == 1) {
		if ((int)curr.length () == 1) {
			return result = (curr [0] == 'L');
		} else {
			return result = false;
		}
	}
	
	
	for (int i = 0; i < (int)curr.length (); ++i) {
		if (curr [i] == 'L') {
			int len1 = i;
			int len2 = (int)curr.length () - i - 1;
			
			if (len1 <= (int)end [n - 1].length () && len2 <= (int)end [n - 1].length ()) {
				bool ok1 = true;
				bool ok2 = true;
				
				for (int j = i - 1, k = 0; j >= 0; --j, ++k) {
					if (curr [j] != end [n - 1][k]) {
						ok1 = false;
						break;
					}
				}
				
				if (!ok1) {
					continue;
				}
				
				for (int j = i + 1, k = 0; j < (int)curr.length (); ++j, ++k) {
					if (curr [j] == end [n - 1][k]) {
						ok2 = false;
						break;
					}
				}
				
				if (!ok2) {
					continue;
				}
				return result = true;
			}
		}
	}
	
	if (dfs (n - 1, 0)) {
		return result = true;
	}
	
	if (dfs (n - 1, 1)) {
		return result = true;
	}
	
	
	return result = false;
}


inline void prepare () {
	start [1] = end [1] = "L";
	
	for (int i = 2; i <= n; ++i) {
		start [i] = end [i] = "";
		
		start [i] = mergy (start [i], start [i - 1]);
		start [i] = mergy (start [i], "L");
		start [i] = mergy (start [i], flip (end [i - 1]));
		
		end [i] = mergy (end [i], flip (start [i - 1]));
		end [i] = mergy (end [i], "L");
		end [i] = mergy (end [i], end [i - 1]);
	}
}

inline void solve () {
	static char buffer [1000];
	scanf ("%d%s", &n, buffer);
	
	limit = (int)strlen (buffer);
	
	str [0] = buffer;
	str [1] = flip (reverse (str [0]));
	
	prepare ();
	
	times++;
	
	if (dfs (n, 0)) {
		puts ("Yes");
	} else {
		puts ("No");
	}
}


int main () {
	int test; scanf ("%d", &test);
	for (int i = 1; i <= test; ++i) {
		printf ("Case %d: ", i);
		solve ();
	}
	return 0;
}
