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
 * 全方位木DPみたいな
 * 木における「全頂点間の距離の総和」は典型90にある それに似てる
 * まずは頂点0から全頂点への距離の総和(つまりans[0])を求める(これは単純なDFS)
 * ans[0]の答えを利用して, その子のansを求める
 * ans[to]=ans[from]+(N-cnt[to])-cnt[to](cnt[v]:頂点vを根とする部分木の頂点数)
 * ->ans[from]が求まっているときに, ans[to]への差分は「from->toの辺の寄与がcnt[to]だけ減り, to->fromの辺の寄与がN-cnt[to]だけ増える」
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vvl G(N);
    rep(i, 0, N-1){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
    }

    vl cnt(N); vb vis(N);
    auto dfs = [&](auto dfs, ll v) -> void {
        ll c=1;
        for(auto to : G[v]){
            if(vis[to]) continue;
            vis[to]=true;
            dfs(dfs, to); c+=cnt[to];
        }
        cnt[v]=c;
    };
    vis[0]=true; dfs(dfs, 0);

    vl ans(N);
    vl dist(N, -1); dist[0]=0;
    auto dfs1 = [&](auto dfs1, ll v) -> void {
        for(auto to : G[v]) if(dist[to]==-1){
            dist[to]=dist[v]+1; ans[0]+=dist[to];
            dfs1(dfs1, to);
        }
    };
    dfs1(dfs1, 0);

    vb vis2(N);
    auto dfs2 = [&](auto dfs2, ll v) -> void {
        for(auto to : G[v]){
            if(vis2[to]) continue;
            vis2[to]=true;
            ans[to]=ans[v]+(N-cnt[to])-cnt[to];
            dfs2(dfs2, to);
        }
    };
    vis2[0]=true; dfs2(dfs2, 0);

    rep(i, 0, N) cout << ans[i] << "\n";
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