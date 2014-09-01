#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
vector<string> vec;
vector<string> a;

string get(string a)
{
	string ret;
	for(int i = 1; i <= a.size(); ++ i) {
		if (i < a.size() && a[i] != ' ' && a[i] != '-') continue;
		if (a[i - 1] == ']') ret += '1';
		else ret += '0';
	}
	return ret;
}

int check0()
{
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < a[i].size(); ++ j) {
			if (a[i][j] - '0' != ((j & 1) ^ 1)) {
				return false;
			}
		}
	}
	return true;
}

int check1()
{
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < a[i].size(); ++ j) {
			if (a[i][j] - '0' != ((j & 1))) {
				return false;
			}
		}
	}
	return true;
}

int check2()
{
	int tmp;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < a[i].size(); ++ j) {
			if (j % 3 == 0) tmp = 1;
			else tmp = 0;
			if (a[i][j] - '0' != tmp) {
				return false;
			}
		}
	}
	return true;
}

int check3()
{
	int tmp;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < a[i].size(); ++ j) {
			if (j % 3 == 1) tmp = 1;
			else tmp = 0;
			if (a[i][j] - '0' != tmp) {
				return false;
			}
		}
	}
	return true;
}

int check4()
{
	int tmp;
	for(int i = 0; i < n; ++ i) {
		for(int j = 0; j < a[i].size(); ++ j) {
			if (j % 3 == 2) tmp = 1;
			else tmp = 0;
			if (a[i][j] - '0' != tmp) {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	string tmp, cur;
	cin >> n;
	getline(cin, tmp);
	for(int i = 0; i < n; ++ i) {
		getline(cin, tmp);
		vec.push_back(tmp);
		cur = get(tmp);
		a.push_back(cur);
	}
	if (check0()) {
		cout << "trochee" << endl;
		return 0;
	}
	if (check1()) {
		cout << "iamb" << endl;
		return 0;
	}
	if (check2()) {
		cout << "dactyl" << endl;
		return 0;
	}
	if (check3()) {
		cout << "amphibrach" << endl;
		return 0;
	}
	if (check4()) {
		cout << "anapaest" << endl;
		return 0;
	}
	cout << "not a poem" << endl;
	return 0;
}
