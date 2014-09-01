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

const int month[31]={0,31,28,31,30,31,30,31,31,30,31,30,31};

namespace Julian{
	struct Date{
		int yy,mm,dd;
		bool init(){return scanf("%d-%d-%d ",&yy,&mm,&dd)==3;}
		Date(){}
		Date(int yy,int mm,int dd):yy(yy),mm(mm),dd(dd){}
		bool isLeap()const{
			return yy%4==0;
		}
		int NextYear(){
			++yy;
			return 365+isLeap();
		}
		void NextDay(){
			++dd;
			if(dd>month[mm]+(mm==2&&isLeap())) dd=1,++mm;
			if(mm>12) ++yy,mm=1;
		}
		bool operator <(const Date &a)const{
			if(yy!=a.yy) return yy<a.yy;
			if(mm!=a.mm) return mm<a.mm;
			return dd<a.dd;
		}
	};
}

namespace Gregorian{
	struct Date{
		int yy,mm,dd;
		Date(){}
		Date(int yy,int mm,int dd):yy(yy),mm(mm),dd(dd){}
		bool isLeap()const{
			return yy%400==0||(yy%100!=0&&yy%4==0);
		}
		int NextYear(){
			++yy;
			return 365+isLeap();
		}
		void NextDay(){
			++dd;
			if(dd>month[mm]+(mm==2&&isLeap())) dd=1,++mm;
			if(mm>12) ++yy,mm=1;
		}
		bool operator <(const Date &a)const{
			if(yy!=a.yy) return yy<a.yy;
			if(mm!=a.mm) return mm<a.mm;
			return dd<a.dd;
		}
		void Print(){
			printf("%04d-%02d-%02d\n",yy,mm,dd);
		}
	};
}

Julian::Date now(1582,10,4),Read;
Gregorian::Date ans(1582,10,15),recG[10001][13][32];

int main() {
	while(now.yy<10000){
		recG[now.yy][now.mm][now.dd]=ans;
		now.NextDay(),ans.NextDay();
	}
	while(Read.init()){
		recG[Read.yy][Read.mm][Read.dd].Print();
	}
	return 0;
}