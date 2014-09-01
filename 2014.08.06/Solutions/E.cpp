#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define ll long long

using namespace std;

const int N = 200005;

struct point
{
	ll x, y, id;
} p[N], Now[N], rnow[25], pnow, px;

struct TA {
	ll Val;
	ll id;
} Ans[16];

ll cmp1(point a, point b) {
	return a.x < b.x;
}

ll cmp2(point a, point b) {
	return a.y < b.y;
}

ll tt, n, i, r, b, m, tot, Root;
ll test;
ll Left[N], Right[N];


ll Cross(ll x1, ll y1, ll x2, ll y2) {
	return (x1) * (y2) - (x2) * (y1);
}

ll Cross(point a, point b, point c) {
	return Cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

ll Inline(point a, point b, point c) {
	if (Cross(a, b, c) != 0)
		return 0;
	if (a.x >= min(b.x, c.x) && a.x <= max(b.x, c.x) && a.y >= min(b.y, c.y) && a.y <= max(b.y, c.y))
		return 1;
	return 0;
}

ll xj(point a, point b, point c, point d) {
	ll k1, k2, k3, k4;
	if (Cross(a, b, c) > 0)
		k1 = 1;
	else
		k1 = -1;
	if (Cross(a, b, d) > 0)
		k2 = 1;
	else
		k2 = -1;
	if (Cross(c, d, a) > 0)
		k3 = 1;
	else
		k3 = -1;
	if (Cross(c, d, b) > 0)
		k4 = 1;
	else
		k4 = -1;
	if ((k1 + k2) == 0 && (k3 + k4) == 0)
		return 1;
	return 0;
}

ll in(point p) {
	ll i, s = 0;
	for (i = 1; i < b; i++) {
		if (Inline(p, rnow[i], rnow[i + 1]) == 1)
			return 1;
		s += xj(p, px, rnow[i], rnow[i + 1]);
	}

	s &= 1;
	return s;
}

void Up(point &Now) {
	ll dis;
	TA temp;
	dis = (Now.x - pnow.x) * (Now.x - pnow.x) + (Now.y - pnow.y) * (Now.y - pnow.y);
	if (dis < Ans[2].Val || (dis == Ans[2].Val && Now.id < Ans[2].id)) {
		Ans[2].Val = dis;
		Ans[2].id = Now.id;
		if (Ans[2].Val < Ans[1].Val || (Ans[2].Val == Ans[1].Val && Ans[2].id < Ans[1].id))
			temp = Ans[1], Ans[1] = Ans[2], Ans[2] = temp;
	}
}

ll Make(ll l, ll r, ll wd) {
    ll mid;
	if (l == r) {
        Left[l] = Right[r] = 0;
        return l;
    }

	if (wd == 1)
		sort(Now + l, Now + r + 1, cmp1);
	else
		sort(Now + l, Now + r + 1, cmp2);
	mid = ((l + r) >> 1);
	if (mid - 1 >= l)
		Left[mid] = Make(l, mid - 1, 1 - wd);
	else
		Left[mid] = 0;
	if (mid + 1 <= r)
		Right[mid] = Make(mid + 1, r, 1 - wd);
	else
		Right[mid] = 0;
	return mid;
}

void Ask(ll i, ll wd) {
    if (i == 0)
        return;
	Up(Now[i]);
	if (wd == 1) {
		if (pnow.x <= Now[i].x)
		{
			Ask(Left[i], 1 - wd);
			if ((Now[i].x - pnow.x) * (Now[i].x - pnow.x) <= Ans[2].Val)
				Ask(Right[i], 1 - wd);
		}
		
		else
		{
			Ask(Right[i], 1 - wd);
			if ((Now[i].x - pnow.x) * (Now[i].x - pnow.x) <= Ans[2].Val)
				Ask(Left[i], 1 - wd);
		}
	}
	
	else {
		if (pnow.y <= Now[i].y) {
			Ask(Left[i], 1 - wd);
			if ((Now[i].y - pnow.y) * (Now[i].y - pnow.y) <= Ans[2].Val)
				Ask(Right[i], 1 - wd);
		}
		
		else {
			Ask(Right[i], 1 - wd);
			if ((Now[i].y - pnow.y) * (Now[i].y - pnow.y) <= Ans[2].Val)
				Ask(Left[i], 1 - wd);
		}
	}
	
	return;
}

void Work(ll Region) {
	ll i;
	printf("Region %lld\n", Region);
	scanf("%lld", &b);
	for (i = 1; i <= b; i++)
		scanf("%lld %lld", &rnow[i].x, &rnow[i].y);
    rnow[b + 1] = rnow[1];
    b++;
	tot = 0;
	for (i = 1; i <= n; i++)
		if (in(p[i]) == 1)
			Now[++tot] = p[i];
	Root = Make(1, tot, 1);

	scanf("%lld", &m);
	for (i = 1; i <= m; i++) {
		scanf("%lld %lld", &pnow.x, &pnow.y);
		Ans[1].Val = Ans[2].Val = 100000000000000LL;
		Ask(Root, 1);
        printf("%lld %lld\n", Ans[1].id, Ans[2].id);
	}
	
	return;
}

int main()
{
	px.x = 944541219;
	px.y = 198523843;
    scanf("%lld", &test);
    while (test--) {
        tt++;
        printf("Case #%lld:\n", tt);
        scanf("%lld", &n);
        for (i = 1; i <= n; i++)
            scanf("%lld %lld", &p[i].x, &p[i].y), p[i].id = i;
        scanf("%lld", &r);
        for (i = 1; i <= r; i++)
            Work(i);
    }

    return 0;
}
