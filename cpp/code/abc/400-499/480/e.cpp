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
 * 初項A1は必ず1以上10^6以下だから全探索可能
 * 公差を探索したいけど1~1e9程度まで存在するため全探索はできない
 * 項数に着目する 最長は1*2*3*...*20>10^18より項数は最長で19
 * 初項(~10^6)と項数(~19)を固定したときに、公差に対して総積が単調増加のため、公差を二分探索可能
 * シンプルな実装だと10^18で5s程度 枝刈りをすると327ms
 */
void solve() {
    ll N; cin >> N;
    ll ans=0;

    auto check = [&](ll a1, ll len, ll x) -> bool {
        // 初項a1, 公差x, 長さlenの等差数列の総積がN以下(true), 超過(false)
        ll val=a1;
        ll sum=1;
        rep(i, 0, len){
            if(sum>N/val) return false;
            sum*=val;
            val+=x;
        }
        return sum<=N;
    };

    rep(a1, 1, 1000001){
        // 初項をa1で固定]
        if(!check(a1, 3, 1)) break; // 枝刈り
        rep(len, 3, 20){
            // 数列の長さをlenで固定
            if(!check(a1, len, 1)) break; // 枝刈り
            // 公差を二分探索する
            ll l=0, r=1e9;
            while(r-l>1){
                ll m=(l+r)/2;
                if(check(a1, len, m)) l=m;
                else r=m;
            }
            ans+=l;
        }
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}