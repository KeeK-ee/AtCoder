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
using mint = modint998244353;

const ll INF = 1e18;
const ll MOD = 998244353;
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

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * BFSっぽい
 * 空きマスだけで到達可能のときは当然到達可能
 * 壁マスについて下の壁マスを全て破壊可能の場合に到達可能
 * 「同列の下の壁マスを全て破壊可能の場合」->これを高速に求める
 * ある行からの遷移を始める前に上記を更新しておく
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, C; cin >> N >> C;
    vs S(N); rep(i, 0, N) cin >> S[i];

    vvb vis(N, vb(N)); vis[N-1][C-1]=true;
    queue<pll> q; q.push({N-1, C-1});

    vb rm(N, true);

    ll pre=N;
    while(!q.empty()){
        auto [y, x]=q.front(); q.pop();
        if(pre!=y){
            rep(i, 0, N) if(S[y][i]=='#' && !vis[y][i]) rm[i]=false;
            pre=y;
        }
        rep(i, -1, 2){
            ll ny=y-1, nx=x+i;
            if(outOfGrid(ny, nx, N, N)) continue;
            if(vis[ny][nx]) continue;
            if(S[ny][nx]=='.'){
                vis[ny][nx]=true; q.push({ny, nx}); continue;
            }
            if(rm[nx]){
                vis[ny][nx]=true; q.push({ny, nx}); continue;
            }
        }
    }

    rep(i, 0, N){
        if(vis[0][i]) cout << 1;
        else cout << 0;
    }
    cout << "\n";
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