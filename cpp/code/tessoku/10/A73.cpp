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
 * ダイクストラ法の基準となる変数が2種類(距離が小さい方がいい, 木は多い方がいい)
 */
void solve() {
    ll N, M; cin >> N >> M;
    Vec<Vec<tuple<ll, ll, ll>>> G(N);
    rep(i, 0, M){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--;
        G[a].push_back({b, c, d}); G[b].push_back({a, c, d});
    }

    Vec<pll> dist(N, {INF, 0}); dist[0]={0, 0};
    pq_min<tuple<ll, ll, ll>> q;
    q.push({0, 0, 0}); //{その頂点への現時点の最小コスト, 木の数のmax, 頂点番号}

    while(!q.empty()){
        auto [d, t, to] = q.top(); q.pop();
        if(dist[to].first!=d and dist[to].second!=t) continue; //確定している
        for(auto [nv, nd, nt] : G[to]){
            if(dist[nv].first<d+nd) continue; //更新せず
            else if(dist[nv].first==d+nd){
                if(dist[nv].second>=t+nt) continue;
            }
            dist[nv].first=d+nd; dist[nv].second=t+nt;
            q.push({d+nd, t+nt, nv});
        }
    }

    cout << dist[N-1].first << " " << dist[N-1].second << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}