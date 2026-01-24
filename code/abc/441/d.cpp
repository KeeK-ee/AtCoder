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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

// AC(グローバルでのDFS)

// ll N, M, L, S, T;
// vector<vector<pll>> G(N);
// vb ans(N);

// void dfs(ll v, ll cnt, ll cst){
//     if(cnt==L){
//         if(S<=cst && cst<=T) ans[v]=true;
//         return;
//     }
//     for(auto[to, c] : G[v]){
//         dfs(to, cnt+1, cst+c);
//     }
// }

// void solve() {
// // ロジックをちゃんと考える！！！
//     cin >> N >> M >> L >> S >> T;
//     G = vector<vector<pll>>(N);
//     rep(i, 0, M){
//         ll u, v, c; cin >> u >> v >> c;
//         u--;v--;
//         G[u].push_back({v, c});
//     }

//     ans = vb(N, false);
//     dfs(0, 0, 0);
//     rep(i, 0, N)if(ans[i]) cout << i+1 << " ";
// }

/**
 * DFSをしそう->どのようなDFS?
 * v(1<=v<=N)をループしてそれぞれDFS?
 * ->そんなことはしなくてよい. 始点が必ず1で深さがLで終了するから
 * 終了時点でvにいれば、vのフラグを立てるという設計
 * つまり1回のDFSでよい
 * 計算量は最悪の場合, 4回の分岐をL回行うから4^L(だいたい10^6くらい)
 */

// ラムダ式でのDFS
void solve(){
    ll N, M, L, S, T;
    cin >> N >> M >> L >> S >> T;
    vector<vector<pll>> G(N);
    rep(i, 0, M){
        ll u, v, c; cin >> u >> v >> c;
        u--;v--;
        G[u].push_back({v, c});
    }
    vb ans(N, false);

    //dfsする
    auto dfs = [&](auto dfs, ll v, ll cnt, ll cst) -> void {
        if(cnt==L){
            if(S<=cst && cst<=T) ans[v]=true;
            return;
        }
        for(auto[to, c] : G[v]){
            dfs(dfs, to, cnt+1, cst+c);
        }
    };

    dfs(dfs, 0, 0, 0);
    rep(i, 0, N)if(ans[i]) cout << i+1 << " ";
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