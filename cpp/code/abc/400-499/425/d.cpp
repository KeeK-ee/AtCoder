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

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * BFSで同時に更新をするために, すぐに更新せず一時的に別のキューに退避
 * BFS用のキューが空になったら, 更新した世代を反映してキューに突っ込む
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];

    vvb grid(H, vb(W));
    queue<pll> q, qq;
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='#'){
            grid[i][j]=true; q.push({i, j});
        }
    }

    while(!q.empty()){
        auto [y, x]=q.front(); q.pop();
        rep(i, 0, 4){
            ll ny=y+dy4[i], nx=x+dx4[i];
            if(outOfGrid(ny, nx, H, W)) continue;
            if(grid[ny][nx]) continue;
            ll cnt=0;
            rep(j, 0, 4){
                ll nny=ny+dy4[j], nnx=nx+dx4[j];
                if(outOfGrid(nny, nnx, H, W)) continue;
                if(grid[nny][nnx])cnt++;
            }
            if(cnt==1){
                qq.push({ny, nx});
            }
        }
        if(q.empty()){
            while(!qq.empty()){
                auto [y, x]=qq.front(); qq.pop(); q.push({y, x});
                grid[y][x]=true;
            }
        }
    }

    ll ans=0;
    rep(i, 0, H)rep(j, 0, W)if(grid[i][j])ans++;
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