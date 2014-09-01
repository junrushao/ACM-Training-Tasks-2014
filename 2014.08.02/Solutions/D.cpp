#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef __int64 ll;
const double pi = acos(-1.0);
const int N = 10000+5;
const double eps = 1e-6;
const int MOD = 119;

struct Complex {
        double x,y;
        Complex(double _x=0,double _y=0)
                        :x(_x),y(_y) {}
        Complex operator + (const Complex& tt)const { return Complex(x+tt.x,y+tt.y); }
        Complex operator - (const Complex& tt)const { return Complex(x-tt.x,y-tt.y); }
        Complex operator * (const Complex& tt)const { return Complex(x*tt.x-y*tt.y,x*tt.y+y*tt.x); }
};
void FFT(Complex *a, int n, int rev) {
        // n是大于等于相乘的两个数组长度的2的幂次
        // 从0开始表示长度，对a进行操作
        // rev==1进行DFT，==-1进行IDFT
        for (int i = 1,j = 0; i < n; ++ i) {
                for (int k = n>>1; k > (j^=k); k >>= 1);
                if (i<j) swap(a[i],a[j]);
        }
        for (int m = 2; m <= n; m <<= 1) {
                Complex wm(cos(2*pi*rev/m),sin(2*pi*rev/m));
                for (int i = 0; i < n; i += m) {
                        Complex w(1.0,0.0);
                        for (int j = i; j < i+m/2; ++ j) {
                                Complex t = w*a[j+m/2];
                                a[j+m/2] = a[j] - t;
                                a[j] = a[j] + t;
                                w = w * wm;
                        }
                }
        }
        if (rev==-1) {
                for (int i = 0; i < n; ++ i) a[i].x = (a[i].x/n+eps);
        }
}
int n, a, b, p, q;

bool input() {
    return scanf("%d%d%d%d%d", &n, &a, &b, &p, &q) == 5;
}

Complex a1[N<<2], a2[N<<2];
ll Fuck[N<<2];

void Add(int &x, int y) {
    x += y;
    if(x >= MOD)    x -= MOD;
}

void mul(int *tmp1, int *tmp2, int maxn) {
    //for(int i = 0;i < q; i++)   printf("%d ", tmp1[i]); puts("");
    //for(int i = 0;i < q; i++)   printf("%d ", tmp2[i]); puts("");
    for(int i = 0;i < maxn; i++) {
        a1[i].x = a1[i].y = a2[i].x = a2[i].y = 0;
        if(i < q)   {
            a1[i].x = 1.0*tmp1[i];
            a2[i].x = 1.0*tmp2[i];
        }
    }
    FFT(a1, maxn, 1); FFT(a2, maxn, 1);
    for(int i = 0;i < maxn; i++)    a1[i] = a1[i]*a2[i];
    FFT(a1, maxn, -1);
    for(int i = 0;i < maxn; i++)    Fuck[i] = (ll)(a1[i].x+eps)%MOD;
    for(int i = q*2-2;i >= q; i--) {
        if(Fuck[i]) {
            Fuck[i-q] = (Fuck[i-q] + Fuck[i]*b)%MOD;
            Fuck[i-p] = (Fuck[i-p] + Fuck[i]*a)%MOD;
        }
    }
    //printf("q = %d\n", q);
    for(int i = 0;i < q; i++) {
        tmp1[i] = (int)Fuck[i];
    }
}

int ans[N], tmp[N], f[N];

int solve() {
    a %= MOD; b %= MOD;
    f[0] = 1;
    for(int i = 1;i < q; i++) {
        if(i-p < 0) f[i] = a+b;
        else if(i < q)  f[i] = (a*f[i-p]+b)%MOD;
    }
    if(n < q) {
        return f[n];
    }
    int maxn = 1;
    while(maxn <= (q-1)*2)  maxn <<= 1;
    for(int i = 0;i < q; i++)    ans[i] = tmp[i] = 0;
    ans[0] = 1; tmp[1] = 1;
    int fuck = n;
    while(n) {
        if(n&1) {
            mul(ans, tmp, maxn);
        }
        mul(tmp, tmp, maxn);
        n >>= 1;
    }
    int ret = 0;
    for(int i = 0;i < q; i++) {
        Add(ret, ans[i]*f[i]%MOD);
    }
    n = fuck;
    return ret;
}

int main() {
    while(input()) {
        printf("%d\n", solve());
    }
    return 0;
}

