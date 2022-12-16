#include <bits/stdc++.h>
static constexpr int N = 2e4 + 2e3, K = 1e2 + 5;
int n, k, q, d, ans, cnt, c[N], len[K], a[K][N];
struct Node{
    int v, next1, next2;
    Node(int v = 0, int next1 = 0, int next2 = 0):
        v(v), next1(next1), next2(next2) {}
} b[K][N], tmp[N];
auto Build() -> void  {
    len[k] = n;
    for (int i = 1; i <= n; ++i) b[k][i] = Node(a[k][i], i, 0); // 初始第k个，自己指向第i个位置
    for (int i = k - 1; i; --i) {
        cnt = 0;
        for (int j = 1; j <= len[i + 1]; ++j)
            if ((j + 1) & 1)
                tmp[++ cnt] = b[i + 1][j], tmp[cnt].next2 = j; // 把偶数位的都加入
        int cur1 = 1, cur2 = 1;
        for (int j = 1; j <= n; ++j) {
            while (cur1 <= cnt && tmp[cur1].v <= a[i][j]) { // 求一下它的后继
                tmp[cur1].next1 = j;
                b[i][++ len[i]] = tmp[cur1];
                ++ cur1;
            }
            while (cur2 <= len[i + 1] && b[i + 1][cur2].v <= a[i][j]) ++ cur2; // 求一下在之前序列的位置
            b[i][++ len[i]] = Node(a[i][j], j, cur2);
        }
        while (cur1 <= cnt) { // 求一下剩下最后的一坨 没有后缀
            tmp[cur1].next1 = n + 1;
            b[i][++ len[i]] = tmp[cur1];
            ++ cur1;
        }
    }
    for (int i = 1; i <= len[1]; ++i) c[i] = b[1][i].v; // 得到最终序列
} 
auto main() -> decltype(0) {
    scanf("%d%d%d%d", &n, &k, &q, &d);
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j)
           scanf("%d", a[i] + j);
    Build();
    for (int i = 1, x; i <= q; ++i) {
        scanf("%d", &x);
        x ^= ans;
        ans = 0;
        int p = std::lower_bound(c + 1, c + len[1] + 1, x) - c;
        for (int j = 1; j <= k; ++j) {
            while (p <= len[j] && b[j][p].v < x) ++ p;
            while (p >= 2 && b[j][p - 1].v >= x) -- p; 
            if (p <= len[j]) ans ^= a[j][b[j][p].next1], p = b[j][p].next2;
            else p = len[j + 1] + 1;
        }
        if (!(i % d)) printf("%d\n", ans);
    } return 0;
} 