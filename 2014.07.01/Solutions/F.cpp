#include<stdio.h>
int min(int a,int b){return a<=b?a:b;}
int main()
{
    int x1,x2,x3,x4,xm,y1,y2,y3,y4,ym,T,TT;
    scanf("%d",&TT);
    for(T=1;T<=TT;T++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        x3=y1;y3=-x1;x4=y2;y4=-x2;
        xm=min(x3,x4);ym=min(y3,y4);
        x3-=xm;x4-=xm;y3-=ym;y4-=ym;
        printf("Case %d: %d %d %d %d\n",T,x3,y3,x4,y4);
    }
    return 0;
}

