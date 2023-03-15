#include <bits/stdc++.h>

#define int long long

using PII = std::pair<int, int>;
#define ep emplace
#define eb emplace_back

FILE *fin, *fout, *ferr;

static const int N = 500'005, M = 6'000'005;

int n, m, k, tot, cnt;
int rt[N], ban[N], fail[N], count[N];
std::map<int, int> ch[N], dis[N];
struct TrieNode
{
    int ls, rs, val;
    TrieNode(int ls = 0, int rs = 0, int val = 0) : ls(ls), rs(rs), val(val) {}
} tr[M];
std::vector<PII> e[N];
struct Node
{
    int dis, graph, trie;
    Node(int dis = 0, int graph = 0, int trie = 0) : dis(dis), graph(graph), trie(trie) {}
    // bool operator<(const Node &a) { return dis > a.dis; }
    friend bool operator<(const Node &a, const Node &b) { return a.dis > b.dis; }
};

void insert(int &x, int l, int r, int p, int v)
{
    tr[++tot] = tr[x];
    x = tot;
    if (l == r)
        return tr[x].val = v, void();
    int mid = (l + r) >> 1;
    p <= mid ? insert(tr[x].ls, l, mid, p, v) : insert(tr[x].rs, mid + 1, r, p, v);
}
int query(int x, int l, int r, int p)
{
    if (!x)
        return 0;
    if (l == r)
        return tr[x].val;
    int mid = (l + r) >> 1;
    return p <= mid ? query(tr[x].ls, l, mid, p) : query(tr[x].rs, mid + 1, r, p);
}

signed main()
{
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("Input.txt", "r"), fout = fopen("Output.txt", "w+"), ferr = fopen("Debug.txt", "w+");
    fscanf(fin, "%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        static int u, v, w;
        fscanf(fin, "%lld%lld%lld", &u, &v, &w);
        e[u].eb(v, w), e[v].eb(u, w);
    }
    for (int i = 1; i <= k; ++i)
    {
        static int len;
        fscanf(fin, "%lld", &len);
        int p = 0;
        for (int j = 1; j <= len; ++j)
        {
            static int x;
            fscanf(fin, "%lld", &x);
            if (!ch[p][x])
                ch[p][x] = ++cnt;
            p = ch[p][x];
        }
        ban[p] = true;
    }

    std::queue<int> q1;
    for (auto [GraphId, TrieId] : ch[0])
        insert(rt[0], 1, n, GraphId, TrieId), q1.ep(TrieId);
    while (q1.size())
    {
        int TrieId = q1.front();
        q1.pop();
        rt[TrieId] = rt[fail[TrieId]];
        ban[TrieId] |= ban[fail[TrieId]];
        for (auto [GraphTo, TrieTo] : ch[TrieId])
        {
            insert(rt[TrieId], 1, n, GraphTo, TrieTo);
            fail[TrieTo] = query(rt[fail[TrieId]], 1, n, GraphTo);
            q1.ep(TrieTo);
        }
    }
    if (ban[ch[0][1]])
        return fputs("-1\n", fout), 0;

    std::priority_queue<Node> q2;
    q2.ep(dis[1][ch[0][1]] = 0, 1, ch[0][1]);
    while (q2.size())
    {
        auto [Distance, GraphId, TrieId] = q2.top();
        q2.pop();
        if (count[GraphId] > 20 || dis[GraphId][TrieId] != Distance)
            continue;
        fprintf(ferr, "%lld %lld\n", GraphId, Distance);
        if (GraphId == n)
            return fprintf(fout, "%lld\n", Distance), 0;
        ++count[GraphId];
        for (auto [GraphTo, GraphLink] : e[GraphId])
        {
            int TrieTo = query(rt[TrieId], 1, n, GraphTo);
            if (count[GraphTo] > 20 || ban[TrieTo])
                continue;
            if (!dis[GraphTo].count(TrieTo) || dis[GraphTo][TrieTo] > dis[GraphId][TrieId] + GraphLink)
                q2.ep(dis[GraphTo][TrieTo] = dis[GraphId][TrieId] + GraphLink, GraphTo, TrieTo);
        }
    }
    return fputs("-1\n", fout), 0;
}