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
 * 偏角ソートしてreverseする(時計回りだから)
 * 座標配列自体をsortするわけではなく、pntを基準にordをソートする(参照のために逆引きを作る)
 * 偏角が同じ点があるため
 * l[i]:iと偏角が等しい最小の点のidx
 * r[i]:iと偏角が等しい最大の点のidx
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
    
    ll N, Q; cin >> N >> Q;
    Vec<point> pnt(N); rep(i, 0, N) cin >> pnt[i].x >> pnt[i].y;
    Vec<ll> ord(N); iota(all(ord), 0);
    sort(all(ord), [&](ll i, ll j){ return cmp(pnt[i], pnt[j]); });
    reverse(all(ord));
    // debug_print(ord);
    Vec<ll> rev(N); rep(i, 0, N) rev[ord[i]]=i;

    Vec<ll> l(N), r(N); l[0]=0, r[N-1]=N-1;
    rep(i, 1, N){ 
        l[i]=(cmp(pnt[ord[i]], pnt[ord[i-1]]) ? i : l[i-1]);
     }
    rrep(i, 0, N-1){ 
        r[i]=(cmp(pnt[ord[i+1]], pnt[ord[i]]) ? i : r[i+1]);
     }

    rep(qi, 0, Q){
        ll a, b; cin >> a >> b; a--; b--;
        a=l[rev[a]], b=r[rev[b]];
        if(a<b) out(b-a+1);
        else out(N-(a-b)+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}