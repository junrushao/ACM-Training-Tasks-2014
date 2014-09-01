#include<cctype>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
bool flag;
vector<string> vec;
set<vector<string> > st;
char a[111];
int n;
bool isDot(char c) {
	return c == '.' or c == ',' or c == ':' or c == ';' or c == '?' or c == '!';
}
void parse() {
	bool mis(false);
	vector<string> vec1(vec);
	for(int i = 0; i < (int)vec1.size(); i++) {
		for(int j = 0; j < (int)vec1[i].size(); j++) {
			vec1[i][j] = tolower(vec1[i][j]);
		}
	}
	for(int i = 0; i < (int)vec.size(); i++) {
		for(int j = 1; j <= n; j++) if(i + j <= (int)vec.size()) {
			vector<string> v1(vec1.begin() + i, vec1.begin() + i + j);
			if(st.count(v1)) {
			}else {
				if(flag) {
					mis = true;
					if(j == 1) printf("What does the word \"%s\" mean?\n", vec[i].c_str());
				}
				st.insert(v1);
			}
		}
	}
	if(mis and 1 < (int)vec.size()) {
		printf("What does the sentence \"");
		for(int i = 0; i < (int)vec.size(); i++) {
			printf("%s%c", vec[i].c_str(), i == (int)vec.size() - 1?'\"':' ');
		}
		printf(" mean?\n");
	}
	vec.clear();
}
int main() {
	for(int qq = 1; scanf("%d", &n) == 1; qq++) {
		if(qq > 1)
			printf("\n");
		printf("Learning case %d\n", qq);
		flag = false;
		st.clear();
		vec.push_back("joe");
		parse();
		for(;;) {
			scanf("%s", a);
			if(isDot(a[0])) {
				parse();
			}else if(a[0] == '*') {
				if(!vec.empty())
					parse();
				flag = true;
			}else if(a[0] == '#') {
				if(!vec.empty())
					parse();
				break;
			}else {
				vec.push_back(a);
			}
		}
	}
	return 0;
}
