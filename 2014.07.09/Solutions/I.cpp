#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <complex> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <cassert> 
#include <climits>
using namespace std;

int main()
{
    int T, cas = 0;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        vector<pair<int,int> > fst, snd;
        for (int i = 0; i < n; i++) {
            int ai, bi;
            scanf("%d%d", &ai, &bi);
            fst.push_back(make_pair(ai, i));
            snd.push_back(make_pair(bi, i));
        }
        sort(fst.begin(), fst.end());
        sort(snd.begin(), snd.end());
        vector<int> sum(n, 1);
        int num = n;
        int ptr = 0;
        int ans = INT_MAX;
        for (int i = fst.size(); i >= 0; i--) {
            while (ptr < snd.size() && num < n) {
                if (++sum[snd[ptr].second] == 1)
                    num ++;
                ptr ++;
            }
            ans = min(ans, (i == 0 ? 0 : fst[i-1].first) + (ptr == 0 ? 0 : snd[ptr-1].first));
            if (i > 0) {
                if (--sum[fst[i-1].second] == 0)
                    num --;
            }
        }
        printf("Case %d: %d\n", ++cas, ans);
    }
}