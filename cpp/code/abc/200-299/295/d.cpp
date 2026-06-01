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
 * - 各数字が偶数回現れる区間を数える
 * - 左端固定で考える
 * 左端をiで固定したときに各数に対して0~iに現れる回数の偶奇が分かれば, それが一致する区間をmapでカウントできる
 * ->10要素のタプルで実装
 */
using T = tuple<bool, bool, bool, bool, bool, bool, bool, bool, bool, bool>;
void solve() {
    string S; cin >> S;
    vector<fenwick_tree<ll>> V(10, fenwick_tree<ll>(sz(S)));
    rep(i, 0, sz(S)){
        V[S[i]-'0'].add(i, 1);
    }
    ll ans=0;
    map<T, ll> m;
    m[{true, true, true, true, true, true, true, true, true, true}]++;
    rep(i, 0, sz(S)){
        bool a=V[0].sum(0, i+1)%2==0;
        bool b=V[1].sum(0, i+1)%2==0;
        bool c=V[2].sum(0, i+1)%2==0;
        bool d=V[3].sum(0, i+1)%2==0;
        bool e=V[4].sum(0, i+1)%2==0;
        bool f=V[5].sum(0, i+1)%2==0;
        bool g=V[6].sum(0, i+1)%2==0;
        bool h=V[7].sum(0, i+1)%2==0;
        bool j=V[8].sum(0, i+1)%2==0;
        bool k=V[9].sum(0, i+1)%2==0;
        ans+=m[{a, b, c, d, e, f, g, h, j, k}];
        m[{a, b, c, d, e, f, g, h, j, k}]++;
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