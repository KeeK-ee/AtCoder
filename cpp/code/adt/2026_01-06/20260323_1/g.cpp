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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
using bint = cpp_int;

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * BFSする
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    ll sx, sy, gx, gy; cin >> sx >> sy >> gx >> gy;
    vl x(N), y(N), r(N);
    rep(i, 0, N) cin >> x[i] >> y[i] >> r[i];

    auto on = [&](ll idx, ll xx, ll yy) -> bool {
        return (x[idx]-xx)*(x[idx]-xx) + (y[idx]-yy)*(y[idx]-yy) == r[idx]*r[idx];
    };

    auto reach = [&](ll idx1, ll idx2) -> bool {
        ll d=(x[idx1]-x[idx2])*(x[idx1]-x[idx2]) + (y[idx1]-y[idx2])*(y[idx1]-y[idx2]);
        ll w=(r[idx1]+r[idx2])*(r[idx1]+r[idx2]);
        ll s=(r[idx1]-r[idx2])*(r[idx1]-r[idx2]);
        return s<=d && d<=w;
    };

    ll si=-1, gi=-1;
    rep(i, 0, N){
        if(on(i, sx, sy)) si=i;
        if(on(i, gx, gy)) gi=i;
    }

    vb vis(N); vis[si]=true;
    queue<ll> q; q.push(si);

    while(!q.empty()){
        auto v=q.front(); q.pop();
        rep(i, 0, N) if(!vis[i]) {
            if(reach(v, i)){
                vis[i]=true; q.push(i);
            }
        }
    }

    if(vis[gi]) Yes;
    else No;
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