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


queue< pair<string, int> > list;
map< string, int > repeats;
set< pair<int, string> > container;


inline void solve () {
	static char buffer [1000];
	
	int tick = 0;
	
	while (scanf ("%s", buffer) != EOF) {
		if (buffer [0] == '<') {
			if (buffer [1] == 't' && buffer [2] == 'e' && buffer [3] == 'x' && buffer [4] == 't') {
				tick++;
			} else if (buffer [1] == '/') {
				continue;
			} else if (buffer [1] == 't' && buffer [2] == 'o' && buffer [3] == 'p') {
				int rank;
				scanf ("%d", &rank);
				
				while (!list.empty () && tick - list.front ().second >= 7) {
					string word = list.front ().first;
					
					container.erase (container.find (make_pair (-repeats [word], word)));
					repeats [word]--;
					
					if (repeats [word] > 0) {
						container.insert (make_pair (-repeats [word], word));
					}
					
					list.pop ();
				}
				
				printf ("<top %d>\n", rank);
				
				int cnt = 0, num = 0;
				foreach (it, container) {
					cnt++;
					
					if (cnt <= rank || it -> first == num) {
						printf ("%s %d\n", it -> second.c_str (), -(it -> first));
						num = it -> first;
					} else {
						break;
					}
				}
				
				printf ("</top>\n");
				
				scanf ("%*s");
			} else {
				assert (false);
			}
		} else if ((int)strlen (buffer) >= 4) {
			string word = buffer;
			
			list.push (make_pair (word, tick));
			
			if (repeats [word] == 0) {
				repeats [word] = 1;
			} else {
				container.erase (container.find (make_pair (-repeats [word], word)));
				repeats [word]++;
			}
			
			container.insert (make_pair (-repeats [word], word));
		}
	}
}

int main () {
	solve ();
	return 0;
}
