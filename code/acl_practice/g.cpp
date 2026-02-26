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
using namespace std;

// #include <atcoder/all>
// using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
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
// using mint = modint998244353;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

struct scc_graph {
    int n;
    std::vector<std::vector<int>> g, rg;
    std::vector<int> order;
    std::vector<bool> used;

    scc_graph(int _n) : n(_n), g(_n), rg(_n) {}

    void add_edge(int from, int to) {
        g[from].push_back(to);
        rg[to].push_back(from);
    }

    void dfs(int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) dfs(u);
        }
        order.push_back(v);
    }

    void rdfs(int v, std::vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int u : rg[v]) {
            if (!used[u]) rdfs(u, comp);
        }
    }

    std::vector<std::vector<int>> scc() {
        used.assign(n, false);
        order.clear();
        for (int i = 0; i < n; i++) {
            if (!used[i]) dfs(i);
        }
        
        used.assign(n, false);
        std::vector<std::vector<int>> res;
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i];
            if (!used[v]) {
                std::vector<int> comp;
                rdfs(v, comp);
                res.push_back(comp);
            }
        }
        return res;
    }
};

/**
 * 強連結成分分解->成分を頂点と見なすとDAGになる
 * .scc()後の二次元配列はトポソされている
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    scc_graph G(N);
    rep(i, 0, M){
        ll u, v; cin >> u >> v;
        G.add_edge(u, v);
    }

    auto scc = G.scc();

    out(sz(scc));
    for(auto list : scc){
        cout << sz(list) << " ";
        for(auto v: list) cout << v << " ";
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}