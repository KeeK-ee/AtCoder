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
#define sz(x) (ll)(x).size()
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
 * Pを置換
 * 1 2 3 ..... N
 * P1 P2 P3 .... PN
 * とすると, Pに対してクエリ2を適用した置換Qは
 * P1 P2 P3 .... PN
 * 1 2 3 ..... N
 * になる（逆置換, Pインバース（P-1ともいう））
 * クエリ2が連打されるだけであれば, 最終的な答えはこのうちどちらか
 * よってクエリ1については、上2つの置換の差分更新を行うことを考える
 * 
 * - クエリ2の方が簡単 クエリ2ではPとQのどちらを見るかを入れ替えるから、クエリ2の回数の偶奇やflagで管理
 * - クエリ1について
 *  - Pを見てるとき：swap(P[x], P[y]); swap(Q[P[x]], Q[P[y]]);
 *  - Qを見てるとき：swap(Q[x], Q[y]); swap(P[Q[x]], P[Q[y]]);
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    Vec<ll> P1(N), P2(N);
    rep(i, 0, N) {
        cin >> P1[i]; P1[i]--;
        P2[P1[i]]=i;
    }
    bool rev=false;
    rep(qi, 0, Q){
        int op; cin >> op;
        if(op==1){
            ll x, y; cin >> x >> y; x--; y--;
            if(rev){
                swap(P2[x], P2[y]);
                swap(P1[P2[x]], P1[P2[y]]);
            }
            else{
                swap(P1[x], P1[y]);
                swap(P2[P1[x]], P2[P1[y]]);
            }
        }
        else{
            rev=!rev;
        }
    }
    if(rev) rep(i, 0, N) cout << P2[i]+1 << " ";
    else rep(i, 0, N) cout << P1[i]+1 << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}