#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <ranges>
#include <cctype>
#include <iomanip>
#include <random>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)
#define se second
#define fi first

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

struct CycleDetection {
    int n;                                                     // 頂点数
    bool directed;                                             // true: 有向, false: 無向
    std::vector<std::vector<std::pair<int, int>>> g;           // g[u] = {(to, edge_id), ...}
    int m;                                                     // 辺数

    explicit CycleDetection(int n_, bool directed_)
        : n(n_), directed(directed_), g(n_), m(0) {}

    // 辺を追加 (0-indexed)。自己ループ u==v も OK（有向・無向どちらでもサイクル扱い）
    void add_edge(int u, int v) {
        g[u].emplace_back(v, m);
        if (!directed) g[v].emplace_back(u, m);
        ++m;
    }

    // サイクル(閉路)を構成する頂点列を返す。無ければ空 vector。
    std::vector<int> find_cycle() {
        std::vector<int> color(n, 0);    // 0:未訪問, 1:訪問中(灰), 2:訪問済(黒)
        std::vector<int> par(n, -1);     // DFS 親
        std::vector<int> par_eid(n, -1); // u に入ってきた辺の id（無向で逆走を防ぐため）
        std::vector<int> cycle;

        for (int s = 0; s < n; ++s) {
            if (color[s] != 0) continue;

            std::vector<std::pair<int, int>> stk; // {頂点, 次に見る隣接の index}
            stk.emplace_back(s, 0);
            color[s] = 1;

            while (!stk.empty()) {
                auto& [u, i] = stk.back();
                if (i == (int)g[u].size()) {
                    color[u] = 2;
                    stk.pop_back();
                    continue;
                }
                auto [v, eid] = g[u][i++];

                // 無向では「来た辺そのもの」を逆走しない（多重辺は別 eid なので別扱い）
                if (!directed && eid == par_eid[u]) continue;

                if (color[v] == 0) {
                    color[v] = 1;
                    par[v] = u;
                    par_eid[v] = eid;
                    stk.emplace_back(v, 0);
                } else if (color[v] == 1) {
                    // 後退辺発見: v -> ... -> u -> v が閉路
                    cycle.push_back(v);
                    int cur = u;
                    while (cur != v) {
                        cycle.push_back(cur);
                        cur = par[cur];
                    }
                    std::reverse(cycle.begin(), cycle.end());
                    return cycle;
                }
                // 有向で color[v]==2 は cross/forward edge なので無視
            }
        }
        return {};
    }

    bool has_cycle() { return !find_cycle().empty(); }
};

/**
 * 頂点倍加有向グラフでのサイクル（閉路）検出
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vvl G(N);
    rep(i, 0, M){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
    }
    ll W; cin >> W;
    vs S(N); rep(i, 0, N) cin >> S[i];
    
    CycleDetection CD(N*W, true);

    rep(i, 0, N)rep(j, 0, W){
        if(S[i][j]=='x') continue;
        // その場で留まる
        if(S[i][(j+1)%W]=='o') CD.add_edge(i*W+j, i*W+((j+1)%W));
        // 移動
        for(auto to : G[i]){
            if(S[to][(j+1)%W]=='x') continue;
            CD.add_edge(i*W+j, to*W+((j+1)%W));
        }
    }

    if(CD.has_cycle()) Yes;
    else No;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}