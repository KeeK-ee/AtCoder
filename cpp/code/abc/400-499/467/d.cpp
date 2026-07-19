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

/**
 * 4式の連立方程式を解く->理論上は可能だが、、(kotatsugameさんが4分で通していたため、もっと簡単な方法があるのでは)
 * 円の中心は2点の垂直二等分線上を通る
 * ->2本の垂直二等分線が交差するか(正確に言えば共有点を持つかどうか)判定できればいい
 * - 直線がどちらもy軸に平行(傾きが存在しない)->中点のx座標が等しければok
 * - どちらかがy軸に平行->必ず交わるためok
 * - 直線が平行でない->必ず交わるためok
 * - 直線が平行->2直線が一致する(=y切片が等しい)ならok, そうでないならng
 * 
 * ペナ原因
 * - 2点の垂直二等分線ではなくて、2点を通る直線の交差判定をしてしまう
 * - y軸平行なとき, 中点のx座標ではなくy座標の一致判定をしてしまう(本当になぜ)
 * - 切片の一致計算のとき最大10^9^3の計算があるのにllを使ってオーバーフロー(int128を使うべき)
 */
void solve() {
    ll px, py, qx, qy, rx, ry, sx, sy;
    cin >> px >> py >> qx >> qy >> rx >> ry >> sx >> sy;
    if((py-qy)==0 and (ry-sy)==0) {
        if(px+qx==rx+sx) Yes;
        else No;
    }
    else if((py-qy)==0 or (ry-sy)==0) Yes;
    else{
        if((px-qx)*(ry-sy)==(rx-sx)*(py-qy)) {
            // 切片が等しい->Yes
            int128 a=(int128)(ry*ry-sy*sy)*(py-qy)+(int128)(rx*rx-sx*sx)*(py-qy);
            int128 b=(int128)(py*py-qy*qy)*(ry-sy)+(int128)(px*px-qx*qx)*(ry-sy);
            if(a==b) Yes;
            else No;
        }
        else Yes;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin >> t;
    while (t--) solve();

    return 0;
}