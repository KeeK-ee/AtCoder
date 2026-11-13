/**
 * https://github.com/KeeK-ee/AtCoder/tree/main/cpp/mylib
 */

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
#include <cassert>
#include <limits>
#include <bitset>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;

const ll INF = 2'000'000'000'000'000'000LL; // 2*10^18
const ll MOD = 998244353;
const ld PI = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string DIR = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define Yes cout << "Yes" << "\n"
#define No cout << "No" << "\n"
#define out(x) cout << (x) << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceil_div (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floor_div (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, Vec<T>, greater<T>>;

ll ll_pow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const Vec<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const Vec<Vec<T>>& v) {
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
 * 連結成分ごとに考えて良い
 * サイクルがない(=木)だと達成不能
 * ☆経路、サイクルの偶数奇数は二部グラフに着目
 * 二部グラフ(木を含む)だと達成不能、逆に二部グラフでなければ奇閉路が存在するため(二部グラフと奇閉路が存在することは同値(ABC472-Eの解説を参照))、偶数と奇数のwalkを達成できる
 * 二部グラフではない連結成分(頂点数をnとする)に対するn*(n-1)/2の総和が答え
 */
void solve() {
    ll N, M; cin >> N >> M;
    UnionFind uf(N);
    Vec<Vec<ll>> G(N);
    rep(i, 0, M){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v); G[v].push_back(u);
        uf.merge(u, v);
    }
    
    Vec<ll> c(N);
    ll ans=0;
    for(auto group : uf.groups()){
        bool ok=true;
        ll s=group.front();
        queue<ll> q; q.push(s); c[s]=1;
        while(not q.empty()){
            ll v=q.front(); q.pop();
            for(auto to : G[v]){
                if(c[to]!=0){
                    if(c[to]==c[v]) ok=false;
                }
                else{
                    if(c[v]==1) c[to]=2;
                    else c[to]=1;
                    q.push(to);
                }
            }
        }
        ll siz=group.size();
        if(not ok) ans+=siz*(siz-1)/2;
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