#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1000005;

char str[N];
int s[N], top, len, ansPos;
int test;
char ansChar;

void ok(int pos, char c) {
	if (c <= str[pos]) {
		return;
	}

	if (c == 'a' || c == 'i') {
		s[++top] = c;
		if (len - pos >= top) {
			ansPos = pos;
			ansChar = c;
		}

		top--;
	} else if (c == 'e') {
		if (s[top] == 'a') {
			top--;
			if (len - pos >= top) {
				ansPos = pos;
				ansChar = c;
			}

			s[++top] = 'a';
		}
	} else if (c == 'o') {
		if (s[top] == 'i') {
			top--;
			if (len - pos >= top) {
				ansPos = pos;
				ansChar = c;
			}

			s[++top] = 'i';
		}
	}
}

void work() {
	scanf("%s", str + 1);
	len = strlen(str + 1);
	ansPos = -1;
	top = 0;
	for (int i = 1; i <= len; i++) {
		char c = str[i];
		ok(i, 'o');
		ok(i, 'i');
		ok(i, 'e');
		ok(i, 'a');
		if (c == 'a' || c == 'i') {
			s[++top] = c;
		} else if (c == 'e') {
			if (top && s[top] == 'a') {
				top--;
			} else {
				printf("INVALID\n");
				return;
			}
		} else if (c == 'o') {
			if (top && s[top] == 'i') {
				top--;
			} else {
				printf("INVALID\n");
				return;
			}
		}
	}

	if (top) {
		printf("INVALID\n");
		return;
	}

	if (ansPos == -1) {
		printf("ULTIMATE\n");
		return;
	}

	str[ansPos] = ansChar;
	for (int i = 1; i <= ansPos; i++) {
		char c = str[i];
		if (c == 'a' || c == 'i') {
			s[++top] = c;
		} else {
			top--;
		}
	}

	for (int i = ansPos + 1; i <= len; i++) {
		if (len - i >= top + 1) {
			str[i] = 'a';
			s[++top] = 'a';
		} else {
			if (s[top] == 'a') {
				str[i] = 'e';
			} else {
				str[i] = 'o';
			}

			top--;
		}
	}

	str[len + 1] = 0;
	printf("%s\n", str + 1);
}

int main() {
	scanf("%d", &test);
	while (test--) {
		work();
	}

	return 0;
}

