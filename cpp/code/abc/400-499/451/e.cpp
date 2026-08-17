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

// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

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
// using bint = cpp_int;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}


struct UnionFind {
    std::vector<int> parent_or_size;

    UnionFind(int n) : parent_or_size(n, -1) {}

    int leader(int a) {
        if (parent_or_size[a] < 0) {
            return a;
        }
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int merge(int a, int b) {
        int x = leader(a);
        int y = leader(b);
        if (x == y) return x;
        
        if (-parent_or_size[x] < -parent_or_size[y]) {
            std::swap(x, y);
        }
        
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int size(int a) {
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        int n = parent_or_size.size();
        std::vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        
        std::vector<std::vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        
        std::vector<std::vector<int>> final_result;
        for (int i = 0; i < n; i++) {
            if (!result[i].empty()) {
                final_result.push_back(std::move(result[i]));
            }
        }
        return final_result;
    }
};

/**
 * 各頂点において, 距離が最小の頂点に対しては必ずその頂点への辺が必要
 * クラスカル法
 * あまり分からない
 */
using T = tuple<ll, ll, ll>;
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    priority_queue<T, vector<T>, greater<T>> q;
    vvl A(N, vl(N));
    rep(i, 0, N-1){
        rep(j, i+1, N){
            ll a; cin >> a; q.push({a, i, j});
            A[i][j]=a; A[j][i]=a;
        }
    }
    UnionFind uf(N);
    vvpll G(N);
    while(!q.empty()){
        auto[c, u, v]=q.top(); q.pop();
        if(!uf.same(u, v)){
            uf.merge(u, v);
            G[u].push_back({v, c}); G[v].push_back({u, c});
        }
    }
    rep(i, 0, N){
        vl dist(N, INF); dist[i]=0;
        queue<ll> qu; qu.push(i);
        while(!qu.empty()){
            auto v=qu.front(); qu.pop();
            for(auto [to, c] : G[v]) if(dist[to]==INF){
                dist[to]=dist[v]+c;
                qu.push(to);
            }
        }
        rep(j, 0, N) if(A[i][j]!=dist[j]){
            No; return;
        }
    }
    Yes;
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