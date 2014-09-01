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
#include <bitset>

using namespace std;

typedef long long LL;

#define REP(i, n) for (int i(0); i < (int) (n); i++)

bitset<801> A[3][801];
bitset<801> B[3][801];
int C[801][801];
int n;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int x;
			scanf("%d",&x);
			A[x%3][i][j]=1;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int x;
			scanf("%d",&x);
			B[x%3][j][i]=1;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int zero=(A[0][i]|B[0][j]).count();
			int two=((A[1][i]&B[2][j])|(A[2][i]&B[1][j])).count();
			int one=n-zero-two;
			C[i][j]=(one+two*2)%3;
		}
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) printf("%d%c",C[i][j],j==n?'\n':' ');
	return 0;
}

