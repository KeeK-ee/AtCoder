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
const string dir = "URDL";

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

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * まず無限にシミュレートはできないから法則性がありそう
 * ある程度の回数遷移したら、変化がなくなるか？->そんなことはない
 * 同じ状態をループしそうだが、何回刻みのループか数えるの無理じゃね？
 * "実は"2回刻みのループになる
 * ->ある時点で黒のマスには8近傍に白マスが存在(なぜなら黒に変化するには白の状態で8近傍に黒がないといけないから). その黒と白のセットは2回の周期でループする
 * 広い盤面で中央だけに黒があるところを想像すると黒が伝搬していくことが分かる！？
 * 黒からの距離を多始点BFSで求めておいて偶奇で10^100回後に黒か白か決まる
 * 1回操作後から考えるのは例えば3*3の黒の状態はループしない(1回操作後に全白になったあと周囲から伝搬される)から、自然な状態（？）になるのを待つため
 */
void solve() {
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];
    vvc TMP(H, vc(W, '.'));
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='#') {TMP[i][j]='.'; continue; }
        bool b=false;
        rep(dir, 0, 8){
            ll ni=i+dy8[dir], nj=j+dx8[dir];
            if(outOfGrid(ni, nj, H, W)) continue;
            if(S[ni][nj]=='#'){ b=true; break; }
        }
        if(b) TMP[i][j]='#';
    }
    rep(i, 0, H)rep(j, 0, W){
        S[i][j]=TMP[i][j];
    }
    queue<pll> Q;
    vvl DIST(H, vl(W, INF));
    rep(i, 0, H)rep(j, 0, W)if(S[i][j]=='#'){
        Q.push({i, j}); DIST[i][j]=0;
    }
    while(!Q.empty()){
        auto [i, j]=Q.front(); Q.pop();
        rep(dir, 0, 8){
            ll ni=i+dy8[dir], nj=j+dx8[dir];
            if(outOfGrid(ni, nj, H, W)) continue;
            if(DIST[ni][nj]<=DIST[i][j]+1) continue;
            DIST[ni][nj]=DIST[i][j]+1;
            Q.push({ni, nj});
        }
    }

    rep(i, 0, H){
        rep(j, 0, W){
            if(DIST[i][j]==INF) cout << '.';
            else if(DIST[i][j]%2==0) cout << '.';
            else cout << '#';
        }
        cout << '\n';
    }
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