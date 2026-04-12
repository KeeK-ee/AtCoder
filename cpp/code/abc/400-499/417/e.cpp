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
 * 辞書順->小さいものから貪欲法
 * 頂点番号の小さい順にバックトラック付DFS->6TLE
 * なぜなら最悪計算量がO(N!)
 * 
 * vから辺が伸びる頂点toについて
 * 「すでに訪れた頂点以外でtoからYに行ける」ときそれを選ぶのが最適(貪欲)
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M, X, Y; cin >> N >> M >> X >> Y;
    X--; Y--;
    vvl G(N);
    rep(i, 0, M){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
    }
    rep(i, 0, N) sort(all(G[i]));

    ll v=X;
    vl ans; ans.push_back(X);
    vb vis(N); vis[X]=true;

    auto bfs = [&](ll from, ll to, vb vis) -> bool {
        queue<ll> q; q.push(from); vis[from]=true;
        while(!q.empty()){
            auto v=q.front(); q.pop();
            for(auto w : G[v]){
                if(vis[w]) continue;
                vis[w]=true;
                q.push(w);
            }
        }
        return vis[to];
    };

    while(v!=Y){
        for(auto to : G[v]){
            if(vis[to]) continue;
            // toからYへvis=trueを通らずに行けるか?
            if(bfs(to, Y, vis)){
                ans.push_back(to);
                vis[to]=true;
                v=to;
                break;
            }
        }
    }

    for(auto v : ans) cout << v+1 << " ";
    cout << '\n';
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