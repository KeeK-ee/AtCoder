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

/**
 * C:a[i]=Siから始まる長さT.size()の文字列がTに一致しているかどうか a[i]の累積和とにぶたん
 */
void solve() {
    ll Q; cin >> Q;
    string S, T; cin >> S >> T;
    Vec<ll> a(S.size());
    rep(i, 0, S.size()){
        if(T==S.substr(i, T.size())) a[i]=1;
    }
    Vec<ll> sum(S.size()+1); rep(i, 1, S.size()+1) sum[i]=sum[i-1]+a[i-1];
    // debug_print(sum);
    rep(qi, 0, Q){
        ll l, r; cin >> l >> r; l--; r--;
        auto it=upper_bound(all(sum), sum[l])-sum.begin();
        // cout << (ll)it << "\n";
        if(l<=it-1 and it-1+T.size()-1<=r) Yes;
        else No;
    }
}

/**
 * 累積和が正か否か
 */
void solve2(){
    ll Q; cin >> Q;
    string S, T; cin >> S >> T;
    fenwick_tree<ll> BIT(S.size());
    rep(i, 0, S.size()){
        if(T==S.substr(i, T.size())) BIT.add(i, 1);
    }
    rep(qi, 0, Q){
        ll l, r; cin >> l >> r; l--; r--;
        r-=T.size()-1;
        if(BIT.sum(l, r+1)>0) Yes;
        else No;
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