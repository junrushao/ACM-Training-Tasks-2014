#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n,m;
int d[200000];
vector < int > vec[200000];
int main()
{
    for (;scanf("%d%d",&n,&m)==2;) {
        for (int i=1;i<=n;i++) vec[i].clear();
        for (int i=1;i<=m;i++) {
            int x,y;
            scanf("%d%d",&x,&y);
            vec[x].push_back(y);
        }
        for (int i=1;i<=n;i++) d[i]=0;
        for (int i=0;i<vec[1].size();i++)
            d[vec[1][i]]=vec[1][i];
        for (int i=2;i<=n;i++) {
            for (int j=0;j<vec[i].size();j++) {
                int ne=vec[i][j];
                if (d[ne]==ne) continue;
                if (!d[ne]) d[ne]=d[i];
                else if (d[ne]!=d[i]) d[ne]=ne;
            }
        }
        int ans=0;
        for (int i=1;i<=n;i++)
            for (int j=i+1;j<=n;j++)
                ans+=(d[i]!=d[j]);
        printf("%d\n",ans);
    }
    return 0;
}
