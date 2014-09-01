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

void solve() {
}
int Sign(const double x,double eps=1e-10){
	return x<-eps?-1:x>eps;
}
struct Point{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	void init(){scanf("%lf%lf",&x,&y);}
	Point operator +(const Point &a)const{
		return Point(x+a.x,y+a.y);
	}
	Point operator -(const Point &a)const{
		return Point(x-a.x,y-a.y);
	}
	Point operator /(const double &a)const{
		return Point(x/a,y/a);
	}
	Point operator *(const double &a)const{
		return Point(x*a,y*a);
	}
};
double Det(const Point &a,const Point &b){
	return a.x*b.y-a.y*b.x;
}
double Dot(const Point &a,const Point &b){
	return a.x*b.x+a.y*b.y;
}
bool In_The_Seg(const Point &a,const Point &b,const Point &c){
	return Sign(Dot(a-c,b-c))<=0;
}
bool Seg_Intersect(const Point &a,const Point &b,const Point &c,const Point &d,Point &e){
	double s1=Det(c-a,d-a);
	double s2=Det(d-b,c-b);
	if(!Sign(s1+s2)) return 0;
	e = (b-a)*(s1/(s1+s2))+a;
	return In_The_Seg(a,b,e)&&In_The_Seg(c,d,e);
}
int n,T,m;
struct Triangle{
	Point a[3];
	bool Degenerated()const{return Sign(Det(a[0]-a[2],a[1]-a[2]))==0;}
	void init(){
		a[0].init();
		a[1].init();
		a[2].init();
	}
	Point& operator [](const int dn){
		return a[dn];
	}
}Tri[61];
vector<double> V;
double ans[101];
double now1[101],now2[101];
void build(double now[],double x,bool ignore){
	vector<pair<double,int> > cnt;
	for(int i=1;i<=m;++i){
		vector<double> rec;
		Point e;
		if(ignore&&max(max(Tri[i][0].x,Tri[i][1].x),Tri[i][2].x)<=x+1e-8) continue;
		if(!ignore&&min(min(Tri[i][0].x,Tri[i][1].x),Tri[i][2].x)>=x-1e-8) continue;
		for(int j=0;j<3;++j){
			for(int k=j+1;k<3;++k){
				if(Seg_Intersect(Point(x,-100),Point(x,200),Tri[i][j],Tri[i][k],e)){
					rec.push_back(e.y);
				}
			}
		}
		sort(rec.begin(),rec.end());
		if(rec.size()>1){
			cnt.push_back(make_pair(rec[0],1));
			cnt.push_back(make_pair(rec[int(rec.size())-1],-1));
		}
	}
	for(int i=0;i<=n;++i) now[i]=0;
	sort(cnt.begin(),cnt.end());
	if(!cnt.size()) return;
	double st=cnt[0].first;
	int nc=0;
	for(int i=0;i<int(cnt.size());++i){
		if(nc>0){
			now[nc]+=cnt[i].first-st;
		}
		st=cnt[i].first;
		nc+=cnt[i].second;
	}
}
int main() {
	scanf("%d",&T);
	while(T--){
		V.clear();
		scanf("%d",&n);
		int lastTri=1;
		for(int i=1;i<=n;++i){
			Tri[lastTri].init();
			if(!Tri[lastTri].Degenerated()) ++lastTri;
		}
		m=lastTri-1;
		for(int i=1;i<=m;++i){
			for(int j=0;j<3;++j) V.push_back(Tri[i][j].x);
			for(int j=i+1;j<=m;++j){
				for(int ii=0;ii<3;++ii) for(int jj=ii+1;jj<3;++jj) 
				for(int kk=0;kk<3;++kk) for(int ll=kk+1;ll<3;++ll){
					Point e;
					if(Seg_Intersect(Tri[i][ii],Tri[i][jj],Tri[j][kk],Tri[j][ll],e)){
						V.push_back(e.x);
					}
				}
			}
		}
		sort(V.begin(),V.end());
		V.resize(unique(V.begin(),V.end())-V.begin());
		for(int i=1;i<int(V.size());++i){
			build(now1,V[i-1],1);
			build(now2,V[i],0);
			for(int j=1;j<=n;++j) ans[j]+=(now1[j]+now2[j])/2*(V[i]-V[i-1]);
		}
		for(int i=1;i<=n;++i){
			printf("%.10f\n",ans[i]);
			ans[i]=0;
		}
	}
	return 0;
}