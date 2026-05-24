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
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

vector<mint> fact, inv_fact;

void init_fact(ll N) {
    fact.assign(N+1, 1);
    inv_fact.assign(N+1, 1);
    for (ll i = 1; i <= N; ++i) fact[i] = fact[i-1] * i;
    inv_fact[N] = fact[N].inv();           // ACLのmintはinv()が使える
    for (ll i = N; i >= 1; --i) inv_fact[i-1] = inv_fact[i] * i;
}

mint nCr(ll n, ll r) {
    if (r < 0 || r > n || n < 0) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n-r];
}

mint nCr2 (ll n, ll r){
    mint a=1, b=1;
    rrep(i, n-r+1, n+1) a*=i;
    rep(i, 1, r+1) b*=i;
    mint res =  a*(b.pow((ll)(mint::mod())-2));
    return res.val();
}

void solve() {
    // ロジックをちゃんと考える！！！
    init_fact(1000005);
    ll N; cin >> N;
    vvl G(N);
    rep(i, 1, N){
        ll p; cin >> p; p--;
        G[p].push_back(i);
    }
    vl C(N); rep(i, 0, N) cin >> C[i];
    vl D(N); rep(i, 0, N) cin >> D[i];
    mint ans=1;
    auto dfs = [&](auto dfs, ll v, ll p) -> void {
        for(auto to : G[v]) if(to!=p){
            dfs(dfs, to, v);
            C[v]+=C[to];
        }
        ans*=nCr2(C[v], D[v]);
        C[v]-=D[v];
    };
    dfs(dfs, 0, -1);
    out(ans.val());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}