#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<set>
#include<vector>
#include<cmath>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
#define MP(i,j) make_pair(i,j)
#define X first
#define Y second
typedef long long int64;
typedef long double real;
template <class T>inline void updata(T&a,T b){if(a<b)a=b;}
template <class T>inline void downdata(T&a,T b){if(a>b)a=b;}
template <class T>inline T sqr(const T& x){return x*x;}

const int MaxN = 200000;
const double eps = 1e-8;
struct point{
    double x,y;
    point operator-(point a){
        return (point){x - a.x, y - a.y};
    }
}a[MaxN];
double dis(point x){
    return sqrt(x.x*x.x+x.y*x.y);
}
double cross(point a,point b){
    return a.x * b.y - a.y * b.x;
}
double arctan[MaxN];
int n,T,i;
struct cp{
bool operator()(const int&a,const int&b)
{
    return arctan[a]<arctan[b];
 }
};
typedef set<int,cp>::iterator iterat;
set<int,cp>S;
iterat pre(iterat x)
{
    if (x==S.begin())x=S.end();
    x--;
    return x;
}
iterat nex(iterat x)
{
     x++;
     if (x==S.end())x=S.begin();
     return x;
}
void work()
{
     iterat itr = S.lower_bound(n);
     if (itr==S.end())itr=S.begin();
     point p=a[*itr];
     itr = pre(itr);
     point now=a[*itr];
     if (cross(p - now, a[n] - now)>-eps)return;
     iterat pitr=itr;
     itr = pre(itr);
     p = now;
     now = a[*itr];
     while (cross(p - now, a[n] - now)<eps)
     {
         S.erase(pitr);
         pitr=itr;
         itr=pre(itr);
         p = now;
         now = a[*itr];
     }
     itr = S.lower_bound(n);
     if (itr==S.end())itr=S.begin();
     pitr=itr;
     itr = nex(itr);
     p = a[*pitr];
     now = a[*itr];
     while (cross(now - p, a[n] - p)<eps)
     {
         S.erase(pitr);
         pitr=itr;
         itr=nex(itr);
         p = now;
         now = a[*itr];
     }
     S.insert(n);
 }
int main()
{
    scanf("%d",&T);
    for (int i = 1; i <= 3; i++)
      scanf("%d%lf%lf", &n, &a[i].x, &a[i].y);
    a[0].x = (a[1].x + a[2].x + a[3].x) / 3;
    a[0].y = (a[1].y + a[2].y + a[3].y) / 3;
    for (int i=1;i<= 3; i++)
      arctan[i]=atan2(a[i].y-a[0].y,a[i].x-a[0].x);
    S.insert(1);
    S.insert(2);
    S.insert(3);
    n=3;
      /*for (iterat itr=S.begin();itr != S.end(); itr++)
        printf("%lf %lf\n",a[*itr].x,a[*itr].y);
      puts("");*/
    for (T-=3; T; T--)
    {
      if (scanf("%d",&i),i==1)
      {
          ++n;
          scanf("%lf%lf",&a[n].x,&a[n].y);
          if (dis(a[n]-a[0])>eps)
          {
              arctan[n]=atan2(a[n].y-a[0].y,a[n].x-a[0].x);
              work();
          }
      }
      else
      {
          n++;
          scanf("%lf%lf",&a[n].x,&a[n].y);
          if (dis(a[n]-a[0])>eps)
          {
              arctan[n]=atan2(a[n].y-a[0].y,a[n].x-a[0].x);
              iterat itr = S.lower_bound(n);
              if (itr==S.end())itr=S.begin();
              iterat pitr = pre(itr);
              if (cross(a[*itr]-a[*pitr],a[n]-a[*pitr])>-eps)puts("YES");
              else puts("NO");
          }
          else puts("YES");
      }
      /*for (iterat itr=S.begin();itr != S.end(); itr++)
        printf("%lf %lf\n",a[*itr].x,a[*itr].y);
      puts("");*/
    }
    return 0;
}

