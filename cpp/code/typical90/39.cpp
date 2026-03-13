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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

#include <atcoder/all>
using namespace atcoder;

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
using mint = modint998244353;
using bint = cpp_int;

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
 * 木DPみたいな 寄与を考える
 * 結論はcnt[i]:頂点iの部下の頂点の個数 としてsum((N-cnt[i])*cnt[i])
 * ある辺に対して、その辺の寄与は「その辺より上の頂点の個数*その辺より下の頂点の個数」で計算できる
 * 辺ごとに管理するのは難しいため、頂点に対して上記の個数を管理したい
 * その辺の直下の頂点に対して、「その頂点を含み、部下の頂点の個数」を数えたい
 * →DPみたいなことをする(帰りがけDFS)
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vvl G(N);
    rep(i, 0, N-1){
        ll a, b; cin >> a >> b; a--; b--;
        G[a].push_back(b); G[b].push_back(a);
    }

    vl cnt(N); vb vis(N);
    auto dfs = [&](auto dfs, ll v) -> void {
        ll tmp=1;
        for(auto to : G[v]){
            if(vis[to]) continue;
            vis[to]=true;
            dfs(dfs, to); tmp+=cnt[to];
        }
        cnt[v]=tmp;
    };
    vis[0]=true;
    dfs(dfs, 0);

    ll ans=0;
    rep(i, 0, N) ans+=(N-cnt[i])*cnt[i];
    out(ans);
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