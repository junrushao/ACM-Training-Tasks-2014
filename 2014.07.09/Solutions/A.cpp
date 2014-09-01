#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <bitset>
#include <complex>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cctype>
using namespace std;

const int maxn = 111;

int X[maxn], Y[maxn], N;

void func(int &X, int &Y) {
    for (; X != 1 && Y != 1; ) {
        X /= 2;
        Y /= 2;
    }
}

void main2() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d%d", &X[i], &Y[i]);
    for (int i = 0; i < N; ++i) func(X[i], Y[i]);
    long long nfirst = 0, nsecond = 0;
    for (int i = 0; i < N; ++i) {
        if (X[i] == 1) {
            nsecond += Y[i] - 1;
        } else {
            nfirst += X[i] - 1;
        }
    }
    puts(nfirst > nsecond ? "Alice" : "Bob");
}

int main() {
    int T, caseId = 1;
    for (scanf("%d", &T); T--; ) {
        printf("Case %d: ", caseId++);
        main2();
    }
    return 0;
}