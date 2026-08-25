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

// 重み付きUnion-Find
struct PotentializedUnionFind {
    vector<int> par;
    vector<ll> weight;

    PotentializedUnionFind(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        weight.assign(n, 0);
    }

    int find(int x) {
        if (par[x] == x) {
            return x;
        }
        int root = find(par[x]);
        weight[x] += weight[par[x]];
        return par[x] = root;
    }

    // x, yをw = weight[y]-weight[x]の関係でマージする
    // 戻り値: 矛盾がなければtrue、既存の関係と矛盾すればfalse(マージは行われない)
    bool merge(int x, int y, ll w) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            // 既に同じ連結成分 -> 矛盾がないか確認
            return weight[y] - weight[x] == w;
        }
        par[ry] = rx;
        weight[ry] = w + weight[x] - weight[y];
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    ll diff(int x, int y) {
        // yの重み - xの重み (B_y - B_x)
        return potential(y) - potential(x);
    }
    // ノードxの重み(根からの相対値)を返す
    ll potential(int x) {
        find(x); // 経路圧縮してweight[x]を根からの累積値に更新する
        return weight[x];
    }
};

/**
 * 差分制約は重み付きUF
 * ライブラリに矛盾判定を実装した
 */
void solve() {
    ll N, M; cin >> N >> M;
    PotentializedUnionFind Puf(N);
    rep(i, 0, M){
        ll l, r, d; cin >> l >> r >> d; l--; r--;
        if(!Puf.merge(l, r, d)){ No; return; }
    }
    Yes;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}