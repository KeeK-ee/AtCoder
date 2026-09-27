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
template <typename T> using Vec = vector<T>;
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
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

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

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
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
 * サイクルがあれば適当な変更順序が存在しない
 */
void solve() {
    ll N; cin >> N;
    Vec<string> S(N), T(N);
    rep(i, 0, N) cin >> S[i] >> T[i];
    map<string, ll> m;
    ll n=0;
    rep(i, 0, N){
        if(not m.count(S[i])){ m[S[i]]=n; n++; }
        if(not m.count(T[i])){ m[T[i]]=n; n++; }
    }
    CycleDetection cd(2*N, true);
    rep(i, 0, N){
        cd.add_edge(m[S[i]], m[T[i]]);
    }
    if(cd.has_cycle()) No;
    else Yes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}