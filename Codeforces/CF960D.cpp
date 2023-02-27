# include <bits/stdc++.h>

# define int long long

static const int N = 63;

int n, a[N];
FILE *fin, *fout, *ferr;

int re(int x, int P) {
    return (x % P + P) % P;
}
int inc(int x, int y, int P) {
    x = re(x, P), y = re(y, P);
    return (x + y) % P;
}
int dec(int x, int y, int P) {
    x = re(x, P), y = re(y, P);
    return (x + P - y) % P;
}

int PosToId(int p) {
    int l = (int)std::log2(p);
    p = inc(p, a[l], 1ll << l) + (1ll << l);
    return p;
}
int IdToPos(int p) {
    int l = (int)std::log2(p);
    p = dec(p, a[l], 1ll << l) + (1ll << l);
    return p;
}

void solve() {
    static int opt, x, y;
    fscanf(fin, "%lld", &opt);

    if (opt == 1) {
        fscanf(fin, "%lld%lld", &x, &y);
        y = -y;
        int c = (int)std::log2(x);
        a[c] = inc(a[c], y, 1ll << c);
    }
    if (opt == 2) {
        fscanf(fin, "%lld%lld", &x, &y);
        y = -y;
        int c = (int)std::log2(x);
        y = re(y, 1ll << c);
        for (int i = c; i < N; ++i) {
            a[i] = inc(a[i], y, 1ll << i);
            y *= 2;
        }
    }
    if (opt == 3) {
        fscanf(fin, "%lld", &x);
        x = IdToPos(x);
        while (x) {
            fprintf(fout, "%lld ", PosToId(x));
            x /= 2;
        }
        fputs("\n", fout);
    }
}

signed main() {
    fin = stdin;
    fout = stdout;
    ferr = stderr;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    // ferr = fopen("Debug.txt", "w+");

    fscanf(fin, "%lld", &n);
    while (n--) solve();
    return 0;
}