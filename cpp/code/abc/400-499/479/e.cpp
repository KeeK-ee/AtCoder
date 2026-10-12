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
 * E：辺の寄与を考える
 * ・連結成分の大きさ比較は各頂点に対して部分木の頂点数を持っておけばOK(dfs1回目)
 * ・値の加算は根を頂点0として(u->vの辺iを考えると)
 * v側の連結成分が大きい→X[v]+=i
 * 〃小さい→X[0]+=i, X[v]-=i
 * (dfs2回目)
 * ・根から葉へ累積和をとればOK(dfs3回目)
 */
void solve() {
    ll N; cin >> N;
    Vec<Vec<ll>> G(N);
    map<pll, ll> mp;
    rep(i, 0, N-1){
        ll a, b; cin >> a >> b; a--; b--;
        mp[{a, b}]=i+1; mp[{b, a}]=i+1;
        G[a].push_back(b); G[b].push_back(a);
    }
    Vec<ll> cnt(N);
    auto dfs1=[&](auto dfs1, ll v, ll p) -> void {
        ll c=1;
        for(auto to : G[v])if(to!=p){
            dfs1(dfs1, to, v);
            c+=cnt[to];
        }
        cnt[v]=c;
    }; dfs1(dfs1, 0, -1);
    Vec<ll> X(N);
    auto dfs2=[&](auto dfs2, ll v, ll p) -> void {
        for(auto to : G[v])if(to!=p){
            if(cnt[to]<N-cnt[to]){
                X[0]+=mp[{v, to}];
                X[to]-=mp[{v, to}];
            }
            else{
                X[to]+=mp[{v, to}];
            }
            dfs2(dfs2, to, v);
        }
    }; dfs2(dfs2, 0, -1);
    auto dfs3=[&](auto dfs3, ll v, ll p) -> void {
        for(auto to : G[v])if(to!=p){
            X[to]+=X[v];
            dfs3(dfs3, to, v);
        }
    }; dfs3(dfs3, 0, -1);

    rep(i, 0, N) cout << X[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}