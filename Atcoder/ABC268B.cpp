#include <bits/stdc++.h>
std::string s, t;
auto Check() -> bool {
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] != t[i]) return false;
    } return true;
}
auto main() -> decltype(0) {
    std::cin >> s >> t;
    if (s.size() > t.size()) puts("No");
    else puts(Check() ? "Yes" : "No");
    return 0;
}