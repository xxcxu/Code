#include <bits/stdc++.h>

template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}


template<typename T, typename ...Args>
void read(T &x, Args &...args) {
    read(x); read(args...);
}

const int N = 1e5 + 5;

int T, n, cnt;
int f[N], prime[N];
bool mark[N];

void init(int n) {
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mark[i]) {prime[++ cnt] = i; f[i] = f[i - 1];}
        for (int j = 1; j <= cnt; ++j) {
            if (i * prime[j] > n) break;
            mark[i * prime[j]] = true;
            f[i * prime[j]] = f[i] + f[prime[j]];
            if (!(i % prime[j])) break;
        }
    } return void();
}

signed main() {
    read(T); init(N - 1);
    while (T--) {
        read(n);
        bool even = false;
        long long ans = 0;
        for (int i = 1, p, q; i <= n; ++i) {
            read(p, q);
            even |= (p == 2);
            ans += 1ll * f[p] * q;
        } printf("%lld\n", ans + (!even));
    } return 0;
}
