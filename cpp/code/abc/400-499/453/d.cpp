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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
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
#define se second
#define fi first

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * BFSの復元
 * まず、可能かどうかの判定は頂点を4倍した頂点倍加BFSをするだけ
 * 復元について
 * dist[gy][gx][i]が最も小さいものから始める
 * dist[y][x][i]は{y, x}を方向iで訪れたという意味だから{y, x}からの遷移先は
 * 方向iに進んだ座標に決まる(前半で確かめているため必ず到達可能)
 * {ny, nx}から次に進む方向iを決める. これはi=0~3でループしてdistが1少ないかつ
 * 問題の条件(oマスやxマス)を満たすもの
 * 移動条件に方向があるときは方向として見るのではなく, 辺を張れるかどうかの条件として見ると良さそう？
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];
    ll sy, sx, gy, gx;
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='S') sy=i, sx=j;
        if(S[i][j]=='G') gy=i, gx=j;
    }
    vector<vvl> dist(H, vvl(W, vl(4, INF)));
    queue<tuple<ll, ll, ll>> q;
    rep(i, 0, 4){
        q.push({sy, sx, i});
        dist[sy][sx][i]=0;
    }
    while(!q.empty()){
        auto [y, x, d]=q.front(); q.pop();
        rep(i, 0, 4){
            ll ny=y+dy4[i], nx=x+dx4[i];
            if(outOfGrid(ny, nx, H, W)) continue;
            if(S[ny][nx]=='#') continue;
            if(S[y][x]=='o' && d!=i) continue;
            if(S[y][x]=='x' && d==i) continue;
            if(dist[ny][nx][i]<=dist[y][x][d]+1) continue;
            dist[ny][nx][i]=dist[y][x][d]+1;
            q.push({ny, nx, i});
        }
    }
    ll ans=INF;
    rep(i, 0, 4) chmin(ans, dist[gy][gx][i]);
    if(ans>5e6){
        No; return;
    }
    string s;
    const string dir = "URDL";
    tuple<ll, ll ,ll> n;
    rep(i, 0, 4) {
        if(dist[gy][gx][i]==ans){
            n={gy, gx, i}; break;
        }
    }
    while(true) {
        auto [y, x, d]=n;
        if(y==sy&&x==sx){
            break;
        }
        s+=dir[d];
        ll ny=y+dy4[(d+2)%4], nx=x+dx4[(d+2)%4];
        rep(i, 0, 4){
            if(dist[ny][nx][i]+1!=dist[y][x][d]) continue;
            if(S[ny][nx]=='o' && i!=d) continue;
            if(S[ny][nx]=='x' && i==d) continue;
            n={ny, nx, i}; break;
        }
    }
    reverse(all(s));
    Yes; out(s);
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