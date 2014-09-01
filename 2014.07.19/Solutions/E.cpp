#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

int T;
char s[10],ss[10];
int ans;

int main() {
	scanf("%d",&T);
	while(T--){
		scanf("%s%s",s,ss);
		int maxv=0;
		int ans=0;
		for(int i=0;s[i];++i) maxv=max(maxv,s[i]-'0'+1);
		for(int i=0;s[i];++i) ans=ans*maxv+s[i]-'0';
		maxv=0;
		for(int i=0;ss[i];++i) maxv=max(maxv,ss[i]-'0'+1);
		int v=0;
		for(int i=0;ss[i];++i) v=v*maxv+ss[i]-'0';
		printf("%d\n",ans+v);
	}
	return 0;
}
