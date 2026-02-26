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
 * グリッド上のBFS
 * 座標は(y, x)の形を維持
 * continueの処理を確実に
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll R, C; cin >> R >> C;
    ll sy, sx, gy, gx; cin >> sy >> sx >> gy >> gx;
    sy--; sx--; gy--; gx--;
    vs grid(R);
    rep(i, 0, R) cin >> grid[i];
    vvl dist(R, vl(C, -1));
    deque<pll> q;
    q.push_back({sy, sx});
    dist[sy][sx]=0;
    while(!q.empty()){
        auto [y, x] = q.front(); q.pop_front();
        rep(i, 0, 4){
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if(ny < 0 || nx < 0 || ny >=R || nx >= C) continue;
            if(grid[ny][nx]=='#') continue;
            if(dist[ny][nx]!=-1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push_back({ny, nx});
        }
    }
    out(dist[gy][gx]);
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