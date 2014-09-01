#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 500000;

int n, itemID[N], pointID[N], amount[N], order[N];
vector <int> itemIDs, pointIDs;

bool compare(int i, int j) {
    if (pointID[i] == pointID[j]) {
        return itemID[i] < itemID[j];
    }
    return pointID[i] < pointID[j];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", itemID + i, pointID + i, amount + i);
        itemIDs.push_back(itemID[i]);
        pointIDs.push_back(pointID[i]);
        order[i] = i;
    }
    sort(order, order + n, compare);
    sort(itemIDs.begin(), itemIDs.end());
    itemIDs.erase(unique(itemIDs.begin(), itemIDs.end()), itemIDs.end());
    sort(pointIDs.begin(), pointIDs.end());
    pointIDs.erase(unique(pointIDs.begin(), pointIDs.end()), pointIDs.end());
    for (int i = 0, k = 0; i <= (int)pointIDs.size(); ++ i) {
        for (int j = 0; j <= (int)itemIDs.size(); ++ j) {
            if (i == 0 && j == 0) {
                printf("-1");
            } else if (i == 0) {
                printf("%d", itemIDs[j - 1]);
            } else if (j == 0) {
                printf("%d", pointIDs[i - 1]);
            } else {
                while (k < n && pointID[order[k]] < pointIDs[i - 1] && itemID[order[k]] < itemIDs[j - 1]) {
                    k ++;
                }
                int result = 0;
                while (k < n && pointID[order[k]] == pointIDs[i - 1] && itemID[order[k]] == itemIDs[j - 1]) {
                    result += amount[order[k ++]];
                }
                printf("%d", result);
            }
            printf("%c", j == (int)itemIDs.size()? '\n': ' ');
        }
    }
    return 0;
}
