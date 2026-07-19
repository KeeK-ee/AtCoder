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

// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

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
// using bint = cpp_int;

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

/**
 * 全方位木DP
 * ans[0]を求めて差分更新
 */
void solve() {
    ll N; cin >> N;
    vvl G(N);
    rep(i, 0, N-1){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
    }
    
    vl C(N);
    ll total_C = 0; // 木全体の重みの合計
    rep(i, 0, N) {
        cin >> C[i];
        total_C += C[i];
    }

    vl sub(N); // 部分木の重み和
    vl ans(N);
    
    // 1回目のDFS: ans[0] と sub を求める
    // 親へ逆流しないように p(親) を持たせる
    auto dfs1 = [&](auto dfs1, ll v, ll p, ll d) -> void {
        ans[0] += d * C[v]; // 頂点0のコストに足し込む
        sub[v] = C[v];      // 最初は自分自身の重み
        
        for(auto to : G[v]){
            if(to == p) continue;
            dfs1(dfs1, to, v, d + 1);
            sub[v] += sub[to]; // 子の部分木和を足す
        }
    };
    dfs1(dfs1, 0, -1, 0);

    // 2回目のDFS: 差分更新で ans を埋める
    auto dfs2 = [&](auto dfs2, ll v, ll p) -> void {
        for(auto to : G[v]){
            if(to == p) continue;
            // 遷移式：近づく部分を引いて、遠ざかる部分を足す
            ans[to] = ans[v] - sub[to] + (total_C - sub[to]);
            dfs2(dfs2, to, v);
        }
    };
    dfs2(dfs2, 0, -1);

    // 全頂点の中で最小の f(v) を探す
    ll min_ans = INF;
    rep(i, 0, N){
        chmin(min_ans, ans[i]);
    }
    out(min_ans);
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