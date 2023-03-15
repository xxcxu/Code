#include <bits/stdc++.h>

int read()
{
    int t = 0, f = 0;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar())
        t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? ~t + 1 : t;
}

static const int N = 300005, P = 1000000007;

inline int inc(int x, int y) { return (x + y) % P; }
inline int dec(int x, int y) { return (x + P - y) % P; }
inline int mul(int x, int y) { return 1LL * x * y % P; }
inline int qpow(int x, int y)
{
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1)
            ans = mul(ans, x);
    return ans;
}
inline int inv(int x) { return qpow(x, P - 2); }

struct Matrix
{
    int n = 3, m = 3;
    int a[3][3];
    Matrix() {}
    Matrix(int n, int m, int p) : n(n), m(m)
    {
        std::memset(a, 0, sizeof a);
        if (p)
            a[0][0] = a[1][1] = a[2][2] = 1;
    }
    Matrix operator*(const Matrix &a)
    {
        Matrix ans(this->n, a.m, 0);
        for (int i = 0; i < this->n; ++i)
            for (int j = 0; j < a.m; ++j)
                for (int k = 0; k < this->m; ++k)
                    ans.a[i][j] = inc(ans.a[i][j], mul(this->a[i][k], a.a[k][j]));
        return ans;
    }
    Matrix operator+(const Matrix &a)
    {
        Matrix ans(n, m, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.a[i][j] = inc(this->a[i][j], a.a[i][j]);
        return ans;
    }
    Matrix operator^(int k)
    {
        if (!k)
            return Matrix(this->n, this->m, 1);
        Matrix ans = (*this), base = (*this);
        for (--k; k; k >>= 1, base = base * base)
            if (k & 1)
                ans = ans * base;
        return ans;
    }
    Matrix T()
    {
        Matrix ans(m, n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.a[i][j] = this->a[j][i];
        return ans;
    }
};

int n, q, A, B, root;
int a[N];
Matrix v[N];
Matrix F, FT;
Matrix plus, plusT;
Matrix minus, minusT;

struct SegmentTree
{
#define ls lson[x]
#define rs rson[x]
    int id = 0;
    int lson[N << 1], rson[N << 1];
    Matrix s[N << 1], ltag[N << 1], rtag[N << 1];
    void pushup(int x)
    {
        s[x] = s[ls] + s[rs];
        return void();
    }
    void pushtag(int x, Matrix m1, Matrix m2)
    {
        ltag[x] = m1 * ltag[x];
        rtag[x] = rtag[x] * m2;
        s[x] = m1 * s[x] * m2;
        return void();
    }
    void pushdown(int x)
    {
        pushtag(ls, ltag[x], rtag[x]);
        pushtag(rs, ltag[x], rtag[x]);
        ltag[x] = Matrix(3, 3, 1);
        rtag[x] = Matrix(3, 3, 1);
        return void();
    }
    void build(int &x, int l, int r)
    {
        x = ++id;
        ltag[x] = rtag[x] = Matrix(3, 3, 1);
        if (l == r)
        {
            s[x] = plus * v[l - 1] * (minus * v[l + 1]).T();
            return void();
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        return pushup(x);
    }
    void update(int x, int l, int r, int ql, int qr, Matrix m1, Matrix m2)
    {
        if (ql <= l && r <= qr)
            return pushtag(x, m1, m2);
        int mid = (l + r) >> 1;
        pushdown(x);
        if (ql <= mid)
            update(ls, l, mid, ql, qr, m1, m2);
        if (qr > mid)
            update(rs, mid + 1, r, ql, qr, m1, m2);
        return pushup(x);
    }
    Matrix query(int x, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
            return s[x];
        int mid = (l + r) >> 1;
        pushdown(x);
        Matrix ans = Matrix(3, 3, 0);
        if (ql <= mid)
            ans = ans + query(ls, l, mid, ql, qr);
        if (qr > mid)
            ans = ans + query(rs, mid + 1, r, ql, qr);
        return ans;
    }
};
SegmentTree *tree = new SegmentTree; 

void init()
{
    F = Matrix(3, 3, 0);
    F.a[0][0] = 2, F.a[1][0] = F.a[2][0] = 1;
    FT = F.T();
    plus = Matrix(3, 3, 0);
    plus.a[0][0] = 1, plus.a[0][1] = A, plus.a[0][2] = B;
    plus.a[1][0] = 1, plus.a[1][1] = 0, plus.a[1][2] = 0;
    plus.a[2][0] = 0, plus.a[2][1] = 0, plus.a[2][2] = 1;
    plusT = plus.T();
    minus = Matrix(3, 3, 0);
    if (A)
    {
        minus.a[0][0] = 0, minus.a[0][1] = 1, minus.a[0][2] = 0;
        minus.a[1][0] = inv(A), minus.a[1][1] = dec(0, inv(A)), minus.a[1][2] = dec(0, mul(B, inv(A)));
        minus.a[2][0] = 0, minus.a[2][1] = 0, minus.a[2][2] = 1;
    }
    else 
    {
        minus.a[0][0] = 0, minus.a[0][1] = 1, minus.a[0][2] = 0;
        minus.a[1][0] = 0, minus.a[1][1] = 1, minus.a[1][2] = dec(0, B);
        minus.a[2][0] = 0, minus.a[2][1] = 0, minus.a[2][2] = 1;
    }
    minusT = minus.T();
}

signed main()
{
    n = read(), q = read();
    A = read(), B = read();
    init();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= n; ++i)
        v[i] = (plus ^ (a[i] - 2)) * F;
    tree->build(root, 2, n - 1);
    while (q--)
    {
        static char opt[8];
        static int l, r;
        scanf("%s", opt + 1);
        l = read(), r = read();
        if (opt[1] == 'p')
        {
            tree->update(root, 2, n - 1, l + 1, r + 1, plus, Matrix(3, 3, 1));
            tree->update(root, 2, n - 1, l - 1, r - 1, Matrix(3, 3, 1), plusT);
        }
        if (opt[1] == 'm')
        {
            tree->update(root, 2, n - 1, l + 1, r + 1, minus, Matrix(3, 3, 1));
            tree->update(root, 2, n - 1, l - 1, r - 1, Matrix(3, 3, 1), minusT);
        }
        if (opt[1] == 'q')
        {
            printf("%d\n", tree->query(root, 2, n - 1, l + 1, r - 1).a[0][0]);
        }
    }
    return 0;
}