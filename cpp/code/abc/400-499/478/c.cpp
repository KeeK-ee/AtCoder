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
ll op1(ll a, ll b) {return max(a, b);}

ll e1() {return -INF;}

ll op2(ll a, ll b) {return min(a, b);}

ll e2() {return INF;}

/**
 * sortする区間[i, i+K)を全探索する
 * Yesになる条件は
 * - [0, i)が単調増加
 * - [i+K, N)が単調増加
 * - A[i-1]<=[i, i+K)に対する区間min
 * - A[i+K]>=[i, i+K)に対する区間max
 */
void solve() {
    ll N, K; cin >> N >> K;
    Vec<ll> A(N); rep(i, 0, N) cin >> A[i];
    segtree<ll, op1, e1> seg1(A);
    segtree<ll, op2, e2> seg2(A);
    ll l=0, r=N-1;
    rep(i, 0, N-1){
        if(i!=N-1){
            if(A[i]<=A[i+1]) l=i+1;
            else break;
        }
        else l=N-1;
    }
    rrep(i, 1, N){
        if(i!=0){
            if(A[i-1]<=A[i]) r=i-1;
            else break;
        }
        else l=N-1;
    }
    // cout << l << " " << r << '\n';
    if(l>=r) { Yes; return; }
    rep(i, 0, N-K+1){
        if(l+1<i) continue;
        if(i+K<r) continue;
        if(i-1>=0 and A[i-1]>seg2.prod(i, i+K)) continue;
        if(i+K<N and A[i+K]<seg1.prod(i, i+K)) continue;
        Yes; return;
    }
    No;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}