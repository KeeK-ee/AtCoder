/**
 * https://github.com/KeeK-ee/AtCoder/tree/main/cpp/mylib
 */

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
#include <cassert>
#include <limits>
#include <bitset>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;
using mint = modint998244353;

const ll INF = 2'000'000'000'000'000'000LL; // 2*10^18
const ll MOD = 998244353;
const ld PI = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string DIR = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define Yes cout << "Yes" << "\n"
#define No cout << "No" << "\n"
#define out(x) cout << (x) << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceil_div (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floor_div (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, Vec<T>, greater<T>>;

ll ll_pow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const Vec<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const Vec<Vec<T>>& v) {
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
 * 各iについてrが[arg(i), arg(i)+pi)の間に存在する
 * <->
 * iとrの外積が正
 */
void solve() {

    struct point { ll x, y; };
    /**
     * 外積
     * 正：aはbより偏角が小さい
     * 0：aとbの偏角は等しい
     * 負：aはbより偏角が大きい
     */
    auto cross = [&](const point &a, const point &b) -> ll {
        return a.x * b.y - a.y * b.x;
    };
    /**
     * 偏角ソートの比較関数
     * true：aの方が偏角が小さい(aが配列上で前に来る)
     * false:bの方が偏角が小さい(bが配列上で前に来る)
     */
    auto cmp = [&](const point &a, const point &b) -> bool {
        int ah = (a.y < 0 or (a.y == 0 and a.x < 0));
        int bh = (b.y < 0 or (b.y == 0 and b.x < 0));
        if (ah != bh) return ah < bh;
        return cross(a, b) > 0;
    };
    auto argument_sort = [&](Vec<point> &points) {
        sort(points.begin(), points.end(), cmp);
    };

    ll N; cin >> N;
    Vec<point> pnt(N);
    rep(i, 0, N) cin >> pnt[i].x >> pnt[i].y;
    argument_sort(pnt);
    rep(i, N, 2*N) { pnt.push_back(pnt[i-N]); }

    ll ans=0;
    ll r=1;
    rep(i, 0, N){
        if (r <= i) r = i+1;
        while(r<i+N && cross(pnt[i], pnt[r])>0){
          r++;
        }
        chmax(ans, r-i);
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin >> t;
    while (t--) solve();

    return 0;
}