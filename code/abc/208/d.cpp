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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順

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

/**
 * ワ―シャルフロイド法(全点対間最短経路問題)O(N^3)
 * dist[i][j]の初期値:0(i==j), c(i->jに1本の辺を経由してコストcでいける)
 * INF(1本の辺経由ではいけない)
 * k(1~N) i(1~N), j(1~N)でループ
 * dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j])
 * 特にループkの終了時は「1~kまでの辺のみを使用したi->jの最短経路」が記録される
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    ll dist[N][N];
    rep(i, 0, N)rep(j, 0, N){
        if(i==j) dist[i][j]=0;
        else dist[i][j]=INF;
    }
    rep(i, 0, M){
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        dist[a][b]=c;
    }
    ll ans=0;
    rep(k, 0, N)rep(i, 0, N)rep(j, 0, N){
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        //この時点でdist[i][j]:頂点1, 2, ... kまでを使用したときのi->jの最短距離
        if(dist[i][j]!=INF) ans+=dist[i][j];
    }
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