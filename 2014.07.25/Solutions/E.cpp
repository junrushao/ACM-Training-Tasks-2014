#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#include <cstring>
#define PQ priority_queue
#define OO 2147483647
#define Max(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((b) & FASTBUFFER | (a) & ~FASTBUFFER))
#define Min(a, b) ((FASTBUFFER = ((a) - (b)) >> 31), ((a) & FASTBUFFER | (b) & ~FASTBUFFER))
#define Swap(a, b) (a ^= b, b ^= a, a ^= b)

int FASTBUFFER;

using namespace std;

const int N = 2000005;

int len, need, tot;
int s[N], temp[N], top;
char str[N], ans[N];

int work() {
	scanf("%s", str + 1);
	len = strlen(str + 1);
	scanf("%d", &need);
	if (len == 1 && str[1] == '0' && need == 0) {
		return 0;
	}
	
	tot = 0, top = 0;
	need++;
	for (int i = 1; i <= len; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			ans[++tot] = str[i];
			if (tot >= need) {
				break;
			}
		} else if (str[i] >= '0' && str[i] <= '9') {
			int j, now = 0;
			for (j = i; str[j] >= '0' && str[j] <= '9'; j++) {
				now = now * 10 + str[j] - 48;
			}
			
			if (str[j] >= 'A' && str[j] <= 'Z') {
				for (int k = 1; k <= now; k++) {
					ans[++tot] = str[j];
					if (tot >= need) {
						break;
					}
				}
				
				if (tot >= need) {
					break;
				}
				
				i = j;
			} else if (str[j] == '(') {
				s[++top] = now;
				temp[top] = tot;
				i = j;
			}
		} else if (str[i] == ')') {
			int now = s[top], x = temp[top], y = tot;
			for (int j = 1; j < now; j++) {
				for (int k = x + 1; k <= y; k++) {
					ans[++tot] = ans[k];
					if (tot >= need) {
						break;
					}
				}
				
				if (tot >= need) {
					break;
				}
			}
			
			if (tot >= need) {
				break;
			}
			
			top--;
		}
	}
	
	if (tot >= need) {
		printf("%c\n", ans[need]);
		return 1;
	} else {
		printf("0\n");
		return 1;
	}
}

int main() {
	while (work())
		{}
		
	return 0;
}
