#include <bits/stdc++.h>
int a[6];
auto main() -> decltype(0) {
    for (int i = 1; i <= 5; ++i) scanf("%d", a + i);
    std::sort(a + 1, a + 5 + 1);
    int n = std::unique(a + 1, a + 5 + 1) - a - 1;
    printf("%d\n", n);
    return 0;
}