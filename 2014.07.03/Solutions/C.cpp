#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define rep(a,b,c) for(int a=b;a<=c;a++)
#define sqr(x) ((x)*(x))

int T,n1,n2;
double ans1,ans2;
double d1[100],d2[100],xa[100],xb[100],ya[100],yb[100],xka[100],xkb[100],yka[100],ykb[100],ta[100],tb[100];

void check(int X,int Y,double cur){
	double Xa,Xb,Ya,Yb,p;
	Xa=xa[X]+xka[X]*(cur-ta[X]);
	Ya=ya[X]+yka[X]*(cur-ta[X]);
	Xb=xb[Y]+xkb[Y]*(cur-tb[Y]);
	Yb=yb[Y]+ykb[Y]*(cur-tb[Y]);
	p=sqrt(sqr(Xa-Xb)+sqr(Ya-Yb));
	ans1=max(ans1,p);
	ans2=min(ans2,p);
	return	;
}

void work(int X,int Y){
	double lef,rig,K1,K2,B1,B2,tt;
	lef=max(ta[X],tb[Y]);
	rig=min(ta[X+1],tb[Y+1]);
	if	(lef>rig)	return	;
	K1=xka[X]-xkb[Y];
	B1=xa[X]-xb[Y]-xka[X]*ta[X]+xkb[Y]*tb[Y];
	K2=yka[X]-ykb[Y];
	B2=ya[X]-yb[Y]-yka[X]*ta[X]+ykb[Y]*tb[Y];
	tt=-(B1*K1+B2*K2)/(K1*K1+K2*K2);
	check(X,Y,lef);
	check(X,Y,rig);
	if	(tt>lef && tt<rig)	check(X,Y,tt);
	return	;
}

int main(){
	scanf("%d",&T);
	rep(TT,1,T){
		scanf("%d%d",&n1,&n2);
		rep(i,1,n1)	scanf("%lf%lf",&xa[i],&ya[i]);
		rep(i,1,n2)	scanf("%lf%lf",&xb[i],&yb[i]);
		d1[1]=d2[1]=0;
		rep(i,1,n1-1)	d1[i+1]=d1[i]+sqrt(sqr(xa[i+1]-xa[i])+sqr(ya[i+1]-ya[i]));
		rep(i,1,n2-1)	d2[i+1]=d2[i]+sqrt(sqr(xb[i+1]-xb[i])+sqr(yb[i+1]-yb[i]));
		rep(i,1,n1)	ta[i]=100.0*d1[i]/d1[n1];
		rep(i,1,n2)	tb[i]=100.0*d2[i]/d2[n2];
		rep(i,1,n1-1){
			xka[i]=(xa[i+1]-xa[i])/(ta[i+1]-ta[i]);
			yka[i]=(ya[i+1]-ya[i])/(ta[i+1]-ta[i]);
		}
		rep(i,1,n2-1){
			xkb[i]=(xb[i+1]-xb[i])/(tb[i+1]-tb[i]);
			ykb[i]=(yb[i+1]-yb[i])/(tb[i+1]-tb[i]);
		}
		ans1=-1;ans2=1e10;
		rep(i,1,n1-1)	rep(j,1,n2-1)	work(i,j);
		//printf("%.4lf %.4lf\n",ans1,ans2);
		printf("Case %d: %d\n",TT,int(ans1-ans2+0.5));
	}
}
