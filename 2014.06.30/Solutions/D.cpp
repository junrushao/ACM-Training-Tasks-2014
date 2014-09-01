#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long w, h;
long long x, y, c;
long long l, r, u, d;
long long area;
vector< pair<int, int> > vec, ret;

vector<int> construct(int n, int h, long long area)
{
	vector<int> vec;
	for(int i = 0; i < n; ++ i) {
		int tmp = min((long long)h, area);
		vec.push_back(tmp);
		area -= tmp;
	}
	return vec;
}

void solve()
{
	cin >> w >> h >> l >> d >> c;
	area = w * h;
	r = l + c;
	u = d + c;

	long long cur = h;
	long long left;
	if (cur > area / 2) {
		cout << "Impossible" << endl;
		return;
	}

	if (cur == area / 2) {
		vec.push_back(make_pair(1, h));
		vec.push_back(make_pair(1, 0));
		return;
	}

	long long s1 = (l - 1) * h;

	if (cur + s1 >= area / 2) {
		left = area / 2 - cur;
		vector<int> ret = construct(h, l - 1, left);
		for(int i = 0; i < h; ++ i) {
			vec.push_back(make_pair(1 + ret[i], h - i));
			vec.push_back(make_pair(1 + ret[i], h - 1 - i));
		}
		return;
	}

	cur += s1;
	long long s2 = (w - 1 - l) * (h - u);
	if (cur + s2 >= area / 2) {
		left = area / 2 - cur;
		vector<int> ret = construct(h - u, w - 1 - l, left);
		for(int i = 0; i < h - u; ++ i) {
			vec.push_back(make_pair(l + ret[i], h - i));
			vec.push_back(make_pair(l + ret[i], h - 1 - i));
		}
		vec.push_back(make_pair(l, u));
		vec.push_back(make_pair(l, 0));
		return;
	}
	
	cur += s2;
	long long s3 = (w - 1 - l) * d;
	if (cur + s3 >= area / 2) {
		left = area / 2 - cur;
		vector<int> ret = construct(d, w - 1 - l, left);
		vec.push_back(make_pair(w - 1, h));
		vec.push_back(make_pair(w - 1, u));
		vec.push_back(make_pair(l, u));
		vec.push_back(make_pair(l, d));
		for(int i = 0; i < d; ++ i) {
			vec.push_back(make_pair(l + ret[i], d - i));
			vec.push_back(make_pair(l + ret[i], d - 1 - i));
		}
		return;
	}

	cur += s3;
	long long s4 = (w - 1 - r) * (u - d - 1);
	if (cur + s4 >= area / 2) {
		left = area / 2 - cur;
		vector<int> ret = construct(w - 1 - r, u - d - 1, left);
		vec.push_back(make_pair(w - 1, h));
		vec.push_back(make_pair(w - 1, u));
		vec.push_back(make_pair(l, u));
		vec.push_back(make_pair(l, d));
		vec.push_back(make_pair(r, d));
		for(int i = 0; i < w - 1 - r; ++ i) {
			vec.push_back(make_pair(r + i, d + ret[i]));
			vec.push_back(make_pair(r + 1 + i, d + ret[i]));
		}
		vec.push_back(make_pair(w - 1, 0));
		return;
	}

	cout << "Impossible" << endl;
}

void reduce()
{
	vector<pair<int, int> > buf;
	for(int i = 0; i < vec.size(); ++ i) {
		if (i == 0 || vec[i].first != vec[i - 1].first || vec[i].second != vec[i - 1].second) {
			buf.push_back(vec[i]);
		}
	}
	for(int i = 0; i < buf.size(); ++ i) {
		if (ret.size() >= 2) {
			pair<int, int> l1 = ret[ret.size() - 1];
			pair<int, int> l2 = ret[ret.size() - 2];
			if (l1.first == l2.first && l1.first == buf[i].first
				|| l1.second == l2.second && l1.second == buf[i].second) {
				ret.pop_back();
			} 
		}
		ret.push_back(buf[i]);
	}
}

int main()
{
	solve();
	if (vec.size()) {
		reduce();
		cout << ret.size() << endl;
		for(int i = 0; i < ret.size(); ++ i) {
			cout << ret[i].first << ' ' << ret[i].second << endl;
		}
	}
	return 0;
}
