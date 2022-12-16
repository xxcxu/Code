#include <bits/stdc++.h>
class Solution {
public:
    
    int qpow(int x, int y) {
        int ans = 1;
        for (; y; y >>= 1, x *= x) if (y & 1) ans *= x;
        return ans;
    }
    std::size_t;
    std::string crackSafe(int n, int k) {
        int sn = qpow(k, n), fn = qpow(k, n - 1);
        std::vector<int> a(fn, k - 1);
        std::string str(sn + (n - 1), '0');
        for (int i = n - 1, id = 0; i < str.size(); ++i) {
            str[i] = a[id] -- + '0';
            id = id * k - (str[i - (n - 1)] - '0') * fn + a[id] + 1;
        } return str;
    }
};