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
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 8000000000000000000LL; // 8*10^18
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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * 頂点0, N1+N2-1からの最短距離をそれぞれの連結成分で求めて最大値同士を足して
 * それ+1が答え
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N1, N2, M; cin >> N1 >> N2 >> M;
    vvl G(N1+N2);
    rep(i, 0, M){
        ll a, b; cin >> a >> b; a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    queue<ll> q1, q2;
    vl dist(N1+N2, INF);

    q1.push(0);
    dist[0]=0;
    while(!q1.empty()){
        auto v=q1.front(); q1.pop();
        for(auto to : G[v]){
            if(dist[to]<=dist[v]+1) continue;
            dist[to]=dist[v]+1;
            q1.push(to);
        }
    }
    q2.push(N1+N2-1);
    dist[N1+N2-1]=0;
    while(!q2.empty()){
        auto v=q2.front(); q2.pop();
        for(auto to : G[v]){
            if(dist[to]<=dist[v]+1) continue;
            dist[to]=dist[v]+1;
            q2.push(to);
        }
    }

    ll max1=-1, max2=-1;
    rep(i, 0, N1) chmax(max1, dist[i]);
    rep(i, N1, N1+N2) chmax(max2, dist[i]);
    out(max1+max2+1);
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