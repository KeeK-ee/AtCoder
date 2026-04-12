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

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
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
 * 01-BFS
 * コストが0or1のグラフの最短経路問題に使用できる
 * コスト0で移動できる頂点をdequeにpop_front, コスト1で移動できるときdequeにpop_backすることでコスト0のほうを優先して探索する
 * dequeはpush, popがO(1)でできるので, 全体でO(HW)
 * ※ダイクストラはpriority_queueを使うためpush. popがO(logN)で全体でO(NlogN)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    ll sy, sx, gy, gx; cin >> sy >> sx >> gy >> gx;
    sy--; sx--; gy--; gx--;
    vs grid(H);
    rep(i, 0, H) cin >> grid[i];
    vvl dist(H, vl(W, INF));
    dist[sy][sx]=0;
    deque<pll> q;
    q.push_back({sy, sx});
    while(!q.empty()){
        auto [y, x] = q.front(); q.pop_front();
        rep(i, 0, 4){
            ll ny = y + dy[i];
            ll nx = x + dx[i];
            if(ny < 0 || nx < 0 || ny >=H || nx >= W) continue;
            if(grid[ny][nx]=='#') continue;
            if(dist[ny][nx]<=dist[y][x]) continue; //distが同じ場合も探索不要
            dist[ny][nx] = dist[y][x]; //コスト0なので同じ値で更新
            q.push_front({ny, nx});
        }
        rep(i, -2, 3)rep(j, -2, 3){
            ll ny = y + i;
            ll nx = x + j;
            if(ny < 0 || nx < 0 || ny >=H || nx >= W) continue;
            if(grid[ny][nx]=='#') continue;
            if(dist[ny][nx]<=dist[y][x]) continue;
            dist[ny][nx] = dist[y][x]+1;
            q.push_back({ny, nx});
        }
    }

    if(dist[gy][gx]==INF) out(-1);
    else out(dist[gy][gx]);
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