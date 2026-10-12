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
template <typename T> using Vec = vector<T>;
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
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

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

ll op(ll a, ll b) {return min(a, b);}

ll e() {return INF;}

/**
 * s<tの場合を考える
 * 右→左の移動は意味がない(右の時点でtに到達可能だから)
 * すなわち 左0回以上→右1回に限定される
 * 左に2回以上することも意味がない(1回目の左の時点で行きたいところに到達可能だから)
 * よって移動は「左0or1回→右1回」である
 * 左移動0回と1回それぞれで場合分けして計算する
 * 0回：R[s]
 * 1回：L[s]+Rの[0, s)区間min(セグ木)
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    Vec<ll> L(N), R(N);
    rep(i, 1, N) cin >> L[i];
    rep(i, 0, N-1) cin >> R[i];
    segtree<ll, op, e> segL(L);
    segtree<ll, op, e> segR(R);

    rep(qi, 0, Q){
        ll s, t; cin >> s >> t; s--; t--;
        ll ans=INF;
        if(s<t){
            // 直接
            chmin(ans, R[s]);
            // 左→右
            if(s!=0) chmin(ans, L[s]+segR.prod(0, s));
        }
        else{
            // 直接
            chmin(ans, L[s]);
            // 右→左
            if(s!=N-1) chmin(ans, R[s]+segL.prod(s+1, N));
        }
        out(ans);
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