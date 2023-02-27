#include <bits/stdc++.h>

static const int N = 200005;

int n;
char s[N];
FILE *fin, *fout;

void solve()
{
    fscanf(fin, "%d", &n);
    fscanf(fin, "%s", s + 1);
    int cnt1 = 0;
    bool flag = false;
    for (int i = 1; i <= n; ++i)
        if (s[i] == '1')
            ++cnt1;
    for (int i = 2; i <= n; ++i)
        if (s[i] == '1' && s[i - 1] == '1')
            flag = true;
    if (cnt1 & 1)
        fputs("-1\n", fout);
    else if (cnt1 == 2)
    {
        if (n == 3 && flag)
            fputs("-1\n", fout);
        else if (n == 4 && s[2] == '1' && s[3] == '1')
            fprintf(fout, "%d\n", cnt1 / 2 + 2);
        else
            fprintf(fout, "%d\n", cnt1 / 2 + (flag));
    }
    else
        fprintf(fout, "%d\n", cnt1 / 2);
    return void();
}

signed main()
{
    fin = stdin;
    fout = stdout;
    // fin = fopen("Input.txt", "r");
    // fout = fopen("Output.txt", "w+");
    int t;
    fscanf(fin, "%d", &t);
    while (t--)
        solve();
    return 0;
}