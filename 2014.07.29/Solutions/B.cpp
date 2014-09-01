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


int const N = 4;


int const dx [] = {0, 0, 1, -1};
int const dy [] = {1, -1, 0, 0};


int n, ans;
int info [N][N];


inline void dfs (int dep) {
	if (dep > 5 || (ans != -1 && dep >= ans)) {
		return;
	}
	
	bool blank = true;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (info [i][j]) {
				blank = false;
				break;
			}
		}
	}
	
	if (blank) {
		ans = dep;
		return;
	}
	
	
	int backup [N][N];
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			memcpy (backup, info, sizeof (info));
			
			info [i][j]++;
			
			if (info [i][j] >= 5) {
				while (true) {
					vector< pair<int, int> > list;
					
					for (int i = 0; i < n; ++i) {
						for (int j = 0; j < n; ++j) {
							if (info [i][j] >= 5) {
								list.push_back (make_pair (i, j));
								info [i][j] = 0;
							}
						}
					}
					
					if (list.empty ()) {
						break;
					}
					
					foreach (it, list) {
						int x = it -> first;
						int y = it -> second;
					
						for (int k = 0; k < 4; ++k) {
							int currx = x;
							int curry = y;
						
							while (true) {
								if (currx >= 0 && currx < n && curry >= 0 && curry < n) {
									if (info [currx][curry] >= 1) {
										info [currx][curry]++;
										break;
									}
								
									currx += dx [k];
									curry += dy [k];
								} else {
									break;
								}
							}
						}
					}
				}
			}
			
			dfs (dep + 1);
			
			memcpy (info, backup, sizeof (info));
		}
	}
}


int main () {
	n = 4;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf ("%d", info [i] + j);
		}
	}
	
	ans = -1;
	dfs (0);
	
	printf ("%d\n", ans);
	
	return 0;
}
