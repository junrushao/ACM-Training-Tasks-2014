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

#define REP(i, n) for (int i(0); i < (int) (n);i++)

int w,h;
int n;

char s[2][100]={"Block the hole","Too small"};

int C,H;

double Sqrt(double x){
	if(x<1e-8) return 0;
	return sqrt(x);
}

double calc(LL S,LL C,double a){
	return S/a-Sqrt(C*C-a*a);
}

double maxlen(LL S,LL C,double l,double r){
	double mid1,mid2;
	for(int i=1;i<=100;++i){
		mid1=l+(r-l)/3;
		mid2=l+(r-l)/3*2;
		double b1=calc(S,C,mid1);
		double b2=calc(S,C,mid2);
		if(b1<b2) l=mid1;
		else r=mid2;
	}
	return (l+r)/2;
}

int main() {
	scanf("%d%d",&w,&h);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&H,&C);
		bool flag=false;
		if(C>=w){
			//double G=maxlen((LL)H*C,C,w,C);
			double G=w;
			if((LL)H*C*1./G-Sqrt((LL)C*C-G*G)+1e-8>=h){
				flag=true;
			}
		}
		if(C>=h){
//			double G=maxlen((LL)H*C,C,h,C);
			double G=h;
			if((LL)H*C*1./G-Sqrt((LL)C*C-G*G)+1e-8>=w){
				flag=true;
			}
		}
		if(max(w,h)<=max(H,C)&&min(w,h)<=min(H,C)) flag=true;
		printf("%s\n",flag?s[0]:s[1]);
	}
	return 0;
}
