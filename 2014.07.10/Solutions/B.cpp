#include <cstdio>
#include <cstring>

const int N = 2000;

char string[N + 1];
long long result[N][N];

const int C = 26;

struct State {
    State* extend(State*, int);

    int length;
    State* parent;
    State* go[C];
};

int pool_size;
State pool[1 + (N << 1)];

State* newState(int length)
{
    State* s = pool + (pool_size ++);
    s->length = length;
    s->parent = NULL;
    memset(s->go, 0, sizeof(s->go));
    return s;
}

State* State::extend(State* start, int token)
{
    State* p = this;
    State* np = newState(length + 1);
    while (p && !p->go[token]) {
        p->go[token] = np;
        p = p->parent;
    }
    if (!p) {
        np->parent = start;
    } else {
        State* q = p->go[token];
        if (p->length + 1 == q->length) {
            np->parent = q;
        } else {
            State* nq = newState(p->length + 1);
            memcpy(nq->go, q->go, sizeof(q->go));
            nq->parent = q->parent;
            np->parent = q->parent = nq;
            while (p && p->go[token] == q) {
                p->go[token] = nq;
                p = p->parent;
            }
        }
    }
    return np;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t --) {
        scanf("%s", string);
        int n = strlen(string);
        for (int i = 0; i < n; ++ i) {
            pool_size = 0;
            State* start = newState(0);
            long long sum = 0;
            State* p = start;
            for (int j = i; j < n; ++ j) {
                p = p->extend(start, string[j] - 'a');
                sum += p->length - p->parent->length;
                result[i][j] = sum;
            }
        }
        int q;
        scanf("%d", &q);
        while (q --) {
            int l, r;
            scanf("%d%d", &l, &r);
            l --, r --;
            printf("%I64d\n", result[l][r]);
        }
    }
    return 0;
}