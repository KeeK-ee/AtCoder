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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * バックトラックで全探索
 * 全探索の計算量はざっくり4^16=10^9
 * ->来た道には戻らないとして3^16=4*10^7
 * 壁や山にはいけないからもっと少ない->全探索でよさそう
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs grid(H); rep(i, 0, H) cin >> grid[i];

    ll ans=-INF;
    vvb vis(H, vb(W));

    auto dfs = [&](auto dfs, ll sy, ll sx, ll y, ll x, ll k) -> void {
        rep(i, 0, 4){
            ll ny=y+dy4[i], nx=x+dx4[i];
            if(out_of_grid(ny, nx, H, W)) continue;
            if(grid[ny][nx]=='#') continue;
            if(ny==sy&&nx==sx){
                if(k+1<=2) continue;
                chmax(ans, k+1);
            }
            if(vis[ny][nx]) continue;
            vis[ny][nx]=true;
            dfs(dfs, sy, sx, ny, nx, k+1);
            vis[ny][nx]=false;
        }
    };

    rep(i, 0, H){
        rep(j, 0, W){
            if(grid[i][j]=='#') continue;
            vis[i][j]=true;
            dfs(dfs, i, j, i, j, 0);
            vis[i][j]=false;
        }
    }

    if(ans==-INF) out(-1);
    else out(ans);
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