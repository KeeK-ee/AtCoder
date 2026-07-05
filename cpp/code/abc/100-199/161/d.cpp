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

ll GetDigit(ll num){
    if(num==0) return 1;
   ll digit = 0;
   while(num != 0){
      num /= 10;
      digit++;
   }
   return digit;
}

/**
 * 前にくっつけるのは嘘解法
 */
void solve() {
    ll K; cin >> K;
    vl PW10(19); // PW10[i]:10^i
    ll e=1; rep(i, 0, 19) { PW10[i]=e; e*=10; }
    vvl S(19);
    rep(i, 0, 10) S[1].push_back(i);
    if(K<=9) { out(K); return; }

    ll cnt=9;
    rep(d, 2, 19){
        // S[d]:d桁のルンルン数を考える
        if(K<=cnt) break;
        for(auto v : S[d-1]){
            ll dig=GetDigit(v);
            ll t=v/(PW10[dig-1]);
            if(1<=t-1&&t-1<=9){
                S[d].push_back((t-1)*PW10[dig]+v); cnt++;
            }
            if(1<=t&&t<=9) { S[d].push_back(t*PW10[dig]+v); cnt++;}
            if(1<=t+1&&t+1<=9){
                S[d].push_back((t+1)*PW10[dig]+v); cnt++;
            }
        }
    }
    rep(i, 0, 19){
        if(sz(S[i])<=K){ K-=sz(S[i]); continue; }
        sort(all(S[i]));
        out(S[i][K]); break;
    }
    // rep(i, 0, 19){
    //     for(auto v : S[i]) cout << v << " ";
    //     cout << '\n';
    // }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}