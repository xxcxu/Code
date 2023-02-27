#include <bits/stdc++.h>

FILE *fin, *fout, *ferr;

/*
TIPS

n的T次下降幂(T[2, n])
n的i次方(i[1, n])
*/

static const int N = 200'005;

int n, P, ans;
int down[N], power[N];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%d%d", &n, &P);
    down[1] = n;
    for (int i = 2; i <= n; ++i)
        down[i] = mul(down[i - 1], n - i + 1);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = mul(power[i - 1], n);
    for (int i = 2; i <= n; ++i)
        ans = inc(ans, mul(down[i], mul(power[n - i], 1LL * i * (i - 1) / 2 % P)));
    fprintf(fout, "%d\n", ans);
    return 0;
}