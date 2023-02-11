#include <bits/stdc++.h>

using vcd = std::vector<double>;

template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}

#define range Range<int>
template<typename T>
class Iterator {
    public:
        Iterator(T _val = 0): _value(_val) {}
        bool operator != (const Iterator &other) const {
            return this -> _value != other._value;
        }
        const T & operator *() {return _value;}
        T operator ++() {return ++ _value;}
    private:
        T _value;
};
template<typename T>
class Range {
    public:
        Range(T l = 0, T r = 0): __begin(l), __end(r + 1) {}
        Iterator<T> begin() {return Iterator<T>(__begin);}
        Iterator<T> end() {return Iterator<T>(__end);}
    private:
        T __begin;
        T __end;
};

static constexpr double eps = 1e-8;

vcd operator * (vcd a, vcd b) {return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};}
vcd operator - (vcd a, vcd b) {return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};}
vcd operator + (vcd a, vcd b) {return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};}
vcd operator * (vcd a, double k) {return {k * a[0], k * a[1], k * a[2]};}
vcd operator * (double k, vcd a) {return {k * a[0], k * a[1], k * a[2]};}
double operator ^ (vcd a, vcd b) {return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];}
double det(vcd a, vcd b, vcd c) {return a ^ (b * c);}
double len(vcd a) {return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);} // 模长
double dis(vcd a, vcd b) {return len(a - b);}
bool check_para(vcd a, vcd b) { // 是否平行
    vcd ans = a * b;
    for (auto i : range(0, 2)) if (std::fabs(ans[i]) > eps) return false;
    return true;
}

void solve() {
    vcd a(3), b(3), dira(3), dirb(3);
    double ra, rb;
    for (auto i : range(0, 2)) scanf("%lf", &a[i]);
    for (auto i : range(0, 2)) scanf("%lf", &dira[i]);
    scanf("%lf", &ra);
    for (auto i : range(0, 2)) scanf("%lf", &b[i]);
    for (auto i : range(0, 2)) scanf("%lf", &dirb[i]);
    scanf("%lf", &rb);
    if (check_para(dira, dirb)) puts("No");
    else {
        vcd dir = dira * dirb;
        vcd row1 = {dira[0], dirb[0], dir[0]}, row2 = {dira[1], dirb[1], dir[1]};
        vcd row3 = {dira[2], dirb[2], dir[2]}, row4 = {dira ^ a, dirb ^ b, dir ^ a};
        double d = det(row1, row2, row3);
        vcd foot = {det(row4, row2, row3) / d, det(row1, row4, row3) / d, det(row1, row2, row4) / d};
        double verdis = dis(foot, a);
        double nowlen = std::sqrt(ra * ra - verdis * verdis);
        auto point1 = foot + nowlen / len(dir) * dir, point2 = foot - nowlen / len(dir) * dir;
        if ((dis(point1, b) <= rb) ^ (dis(point2, b) <= rb)) puts("Yes");
        else puts("No");
    }
}

signed main() {
    int t; read(t);
    while (t--) solve();
    return 0;
}