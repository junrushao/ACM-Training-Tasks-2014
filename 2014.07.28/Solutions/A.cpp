#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000 + 1;
const int M = 20 + 1;

int c, n, teamID[N], problemID[N], submitTime[N], isAccepted[N], order[N];
int wrongTrialCount[N][M], acceptedTime[N][M], totalSolved[N], penalty[N];

bool compare(int i, int j) {
    return submitTime[i] < submitTime[j];
}

bool compare2(int i, int j) {
    if (totalSolved[i] == totalSolved[j]) {
        if (penalty[i] == penalty[j]) {
            return i < j;
        }
        return penalty[i] < penalty[j];
    }
    return totalSolved[i] > totalSolved[j];
}

int main() {
    scanf("%d%d", &c, &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d%d", teamID + i, problemID + i, submitTime + i, isAccepted + i);
        order[i] = i;
    }
    sort(order, order + n, compare);
    memset(acceptedTime, 0, sizeof(acceptedTime));
    memset(wrongTrialCount, 0, sizeof(wrongTrialCount));
    memset(totalSolved, 0, sizeof(totalSolved));
    memset(penalty, 0, sizeof(penalty));
    for (int iter = 0; iter < n; ++ iter) {
        int i = order[iter];
        if (isAccepted[i] == 1) {
            if (acceptedTime[teamID[i]][problemID[i]] == 0) {
                totalSolved[teamID[i]] ++;
                acceptedTime[teamID[i]][problemID[i]] = submitTime[i];
                penalty[teamID[i]] += submitTime[i] + wrongTrialCount[teamID[i]][problemID[i]] * 20 * 60;
            }
        } else if (acceptedTime[teamID[i]][problemID[i]] == 0) {
            wrongTrialCount[teamID[i]][problemID[i]] ++;
        }
    }
    for (int i = 0; i < c; ++ i) {
        order[i] = i + 1;
    }
    sort(order, order + c, compare2);
    for (int i = 0; i < c; ++ i) {
        printf("%d%c", order[i], i == c - 1? '\n': ' ');
    }
    return 0;
}

