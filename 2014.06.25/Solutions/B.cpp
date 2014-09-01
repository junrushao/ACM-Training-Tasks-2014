
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <assert.h>

using namespace std;
typedef long long LL;
typedef long double LD;

#define PII pair<int, int>
#define sz(X) ((int)((X).size()))

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int maxn = 10000;
int len, tot;
char buf[maxn], b[maxn];

int main(){
	while (gets(buf)){
		len = strlen(buf);
		if (len == 1 && buf[0] == '.') break;
		tot = 0;
		bool ok = true;
		for (int i = 0; i < len; ++i){
			if (buf[i] == '('){
				b[++tot] = '(';
			} else if (buf[i] == ')'){
				if (b[tot] != '('){
					ok = false;
					break;
				}
				--tot;
			} else if (buf[i] == '['){
				b[++tot] = '[';
			} else if (buf[i] == ']'){
				if (b[tot] != '['){
					ok = false;
					break;
				}
				--tot;
			}
		}
		if (tot > 0) ok = false;
		if (ok) puts("yes"); else puts("no");
	}
	return 0;
}
