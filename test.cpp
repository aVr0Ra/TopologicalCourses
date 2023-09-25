#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

inline int read() {
    int x = 0 , f = 1; char ch = getchar();
    for ( ; !isdigit(ch) ; ch = getchar()) if (ch == '-') f = -1;
    for ( ; isdigit(ch) ; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

const int maxn = 1e4 + 10;
const int maxm = 1e5 + 10;

struct Edge {
    int to , next;
}edge[maxm];

int cntEdge , head[maxn];

inline void add_edge(int from , int to) {
    edge[++ cntEdge].to = to;
    edge[cntEdge].next = head[from];
    head[from] = cntEdge;
}

int n , m;

int ind[maxn] , outd[maxn] , depth[maxn];

void dfs(int now , int dep) {
    if (depth[now] >= dep) {
        return ;
    }

    depth[now] = dep;

    for (int e = head[now] ; e ; e = edge[e].next) {
        dfs(edge[e].to , dep + 1);
    }

    return ;
}

int main() {
    n = read() , m = read();
    for (int i = 1 ; i <= m ; i ++) {
        int x = read() , y = read();
        add_edge(x , y);
        ind[y] ++;
        outd[x] ++;
    }

    for (int i = 1 ; i <= n ; i ++) {
        if (!ind[i]) {
            dfs(i , 1);
        }
    }

    for (int i = 1 ; i <= n ; i ++) {
        printf("node %d: depth = %d\n" , i , depth[i]);
    }
}

/*
12 16
1 4 
1 2 
1 12
1 3 
2 3 
4 5 
3 5 
3 7 
5 7
3 8 
9 10
9 12
10 12
9 11
11 6
6 8  
*/