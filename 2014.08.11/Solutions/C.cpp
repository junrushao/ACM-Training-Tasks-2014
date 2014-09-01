#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

const int N = 111111;
const int INF = 1e9 + 10;

const int INPUT = 10 * 4444444;
vector<int> lower[N], upper[N];
int canGet[(1 << 20) + 10], times;

int n, k;
char buffer[INPUT];
string str = "";
int pos = 0, okCount, ans = 0;

struct Tree {
	int maxL, maxR, maxV;
} tree[2 * N];

void build(int k, int l, int r) {
	tree[k].maxL = tree[k].maxR = tree[k].maxV = 0;
	if(l != r) {
		build(k + k, l, (l + r) / 2);
		build(k + k + 1, (l + r) / 2 + 1, r);
	}
}

void edit(int k, int l, int r, int x) {
	if(l == r) {
		tree[k].maxL = tree[k].maxR = tree[k].maxV = (lower[x].back() > 0);
	}else {
		int mid((l + r) / 2);
		if(x <= mid)
			edit(k + k, l, (l + r) / 2, x);
		else
			edit(k + k + 1, (l + r) / 2 + 1, r, x);
		tree[k].maxL = tree[k + k].maxL;
		if (tree[k].maxL == (mid - l + 1)) {
			tree[k].maxL += tree[k << 1 | 1].maxL;
		}
		tree[k].maxR = tree[k + k + 1].maxR;
		if (tree[k].maxR == (r - mid)) {
			tree[k].maxR += tree[k << 1].maxR;
		}
		tree[k].maxV = max(max(tree[k << 1].maxV, tree[k << 1 | 1].maxV), 
			tree[k << 1].maxR + tree[k << 1 | 1].maxL);
	}
}

struct Node {
	int type, val, x;
	// 0 {
	// 1 if
	// 2 else
	Node(int type, int val, int x) : type(type), val(val), x(x) {}
	Node() {}
};

vector<Node> stack;

int nextInt() {
	int res = 0;
	while(str[pos] >= '0' && str[pos] <= '9') {
		res = res * 10 + str[pos] - '0';
		pos++;
	}
	return res;
};

void fresh(int x, int sign) {
	if (lower[x].back() <= upper[x].back()) {
		okCount += sign;
	}
}

void pop() {
	//printf("enter\n");
	while(stack.size() and (stack.back().type == 2 or stack.back().type == 1 and str[pos] != 'e')) {
		if (stack.back().type == 1) {
			int x = stack.back().x;
			fresh(x, -1);
			lower[x].pop_back();
			fresh(x, 1);
			edit(1, 1, n, x);
		} else if (stack.back().type == 2) {
			int x = stack.back().x;
			fresh(x, -1);
			upper[x].pop_back();
			fresh(x, 1);
			edit(1, 1, n, x);
		}
		stack.pop_back();
	
	}
	//printf("mid\n");
	if(stack.size() and stack.back().type == 1) {
		pos += 4;
		stack.back().type = 2;
		fresh(stack.back().x, -1);
		upper[stack.back().x].push_back(min(upper[stack.back().x].back(), stack.back().val - 1));
		lower[stack.back().x].pop_back();
		fresh(stack.back().x, 1);
		edit(1, 1, n, stack.back().x);
	}
	//printf("out\n");
}

void solve() {
	while(str[pos] != '(') {
		pos++;
	}
	pos++;
	n = nextInt();
	pos++;
	k = nextInt();
	okCount = 0;
	for(int i = 1; i <= n; i++) {
		lower[i].clear(); lower[i].push_back(0);
		upper[i].clear(); upper[i].push_back(INF);
		okCount++;
	}
	
	build(1, 1, n);
	
	stack.clear();
	++times;
	
	stack.push_back(Node(0, 0, 0));
	pos += 2;
	ans = 0;
	//cout << str << endl;
	while((int)stack.size()) {
		//printf("%d %d\n", stack.size(), pos);
		if (str[pos] == 'c') {
			//puts("enter CG");
			pos += 3;
			int x = nextInt();
			//printf("%d %d %d %d\n", tree[1].maxV, okCount, n, canGet[x]);
			if (tree[1].maxV <= k && okCount == n) {
				if (canGet[x] != times) {
					canGet[x] = times;
					ans++;
				}
			}
			pos += 2;
			pop();
		} else if (str[pos] == 'i') {
			pos += 5;
			int x = nextInt();
			pos += 3;
			int val = nextInt();
			pos++;
			stack.push_back(Node(1, val, x));
			fresh(x, -1);
			lower[x].push_back(max(lower[x].back(), val));
			fresh(x, 1);
			edit(1, 1, n, x);
		} else if (str[pos] == '{') {
			stack.push_back(Node(0, 0, 0));
			pos++;
		} else if(str[pos] == '}') {
			pos++;
			stack.pop_back();
			pop();
		}
	}
	
	printf("%d\n", ans);
}

int main() {
	while(gets(buffer)) {
		str += buffer;
	}
	string temp = str;
	str = "";
	for(int i = 0; i < temp.size(); i++) {
		if (temp[i] != ' ' && temp[i] != '\t') {
			str += temp[i];
		}
	}
	while(pos < str.size()) {
		solve();
	}
	return 0;
}
