/**
  *https://github.com/KeeK-ee/AtCoder/tree/main/cpp/mylib
***/

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
 * l~rに対する求値はf(r)-f(l-1)典型
 * 1 1+2 1+2+3 1+2+3+4 ....をもってにぶたんでブロック数を求める
 * ブロック部分の総和はA[0]+(A[0]+A[1])+(A[0]+A[1]+A[2])+...なので累積和の累積和
 * あまりの部分はシンプル累積和
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    Vec<ll> A(N); rep(i, 0, N) cin >> A[i];

    Vec<ll> stair; stair.push_back(0);
    rep(i, 1, N+2) stair.push_back(stair.back()+i);

    fenwick_tree<ll> BIT1(N), BIT2(N);
    rep(i, 0, N) BIT1.add(i, A[i]); // i->A[i]
    rep(i, 0, N) {
        BIT2.add(i, BIT1.sum(0, i+1)); // i->0~iまでのsum
    }
    debug_print(stair);

    auto f=[&](ll x) -> ll {
        // B[0]~B[x]までの区間和(O(1)orO(logN)程度で)
        if(x<0) return 0;
        if(x==0) return A[0];
        auto it1=upper_bound(all(stair), x);
        it1--;
        ll res=0;
        // 余り
        res+=BIT1.sum(0, x-*it1+1);
        // 前半全て
        auto it2=upper_bound(all(stair), x)-stair.begin();
        it2--;
        res+=BIT2.sum(0, it2);
        return res;
    };

    rep(qi, 0, Q){
        ll l, r; cin >> l >> r; l--; r--;
        ll ans=f(r)-f(l-1);
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