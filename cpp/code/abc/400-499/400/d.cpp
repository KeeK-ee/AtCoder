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

void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];
    ll sy, sx, gy, gx;
    cin >> sy >> sx >> gy >> gx; sy--; sx--; gy--; gx--;
    
    deque<pll> q; q.push_back({sy, sx});
    vvl dist(H, vl(W, INF)); dist[sy][sx]=0;

    while(!q.empty()){
        auto[y, x]=q.front(); q.pop_front();
        rep(i, 0, 4){
            ll ny=y+dy4[i], nx=x+dx4[i];
            if(outOfGrid(ny, nx, H, W)) continue;
            if(S[ny][nx]=='#') continue;
            if(dist[ny][nx]<=dist[y][x]) continue;
            dist[ny][nx]=dist[y][x];
            q.push_front({ny, nx});
        }
        rep(i, 0, 4){
            ll ny1=y+dy4[i], nx1=x+dx4[i];
            ll ny2=ny1+dy4[i], nx2=nx1+dx4[i];
            if(!outOfGrid(ny1, nx1, H, W) && dist[ny1][nx1]>dist[y][x]+1){
                dist[ny1][nx1]=dist[y][x]+1;
                q.push_back({ny1, nx1});
            }
            if(!outOfGrid(ny2, nx2, H, W) && dist[ny2][nx2]>dist[y][x]+1){
                dist[ny2][nx2]=dist[y][x]+1;
                q.push_back({ny2, nx2});
            }
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