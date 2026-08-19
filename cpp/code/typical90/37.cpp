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

ll op(ll a, ll b) {
    return max(a, b);
}

ll e() { return -INF; }

/**
 * ナップザックDPの応用
 * 遷移にO(W)はかけられない->セグ木でO(logW)で遷移させる
 * vector<segtree>って可能
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll W, N; cin >> W >> N;
    vl L(N), R(N), V(N);
    rep(i, 0, N) cin >> L[i] >> R[i] >> V[i];
    vector<segtree<ll, op, e>> dp(N+1, segtree<ll, op, e>(W+1));
    dp[0].set(0, 0);

    rep(i, 1, N+1){
        rep(j, 0, W+1){
            ll val = dp[i-1].get(j);

            ll l = max(j - R[i-1], 0LL);
            ll r = max(j - L[i-1] + 1, 0LL);
            
            if (l < r) {
                ll mx = dp[i-1].prod(l, r);
                if (mx != -INF) {
                    chmax(val, mx + V[i-1]);
                }
            }
            
            dp[i].set(j, val);
        }
    }

    if(dp[N].get(W)==-INF) out(-1);
    else out(dp[N].get(W));
}

/**
 * 遷移をsegtreeで高速化
 * ll l=max(j-R[i-1], 0LL);
 * ll r=max(j-L[i-1]+1, 0LL);
 * に注意
 */
void solve2(){
    ll W, N; cin >> W >> N;
    vector<ll> L(N), R(N), V(N);
    rep(i, 0, N) cin >> L[i] >> R[i] >> V[i];
    vector<vector<ll>> dp(N+1, vector<ll>(W+1, -INF));
    dp[0][0]=0;
    rep(i, 1, N+1){
        segtree<ll, op, e> seg(W+1);
        rep(j, 0, W+1) seg.set(j, dp[i-1][j]);
        rep(j, 0, W+1){
            // dp[i][j]を決める

            // 料理iを作らない
            chmax(dp[i][j], dp[i-1][j]);

            // 料理iを作る
            // dp[i][j]=dp[i-1][j-R[i-1]]~dp[i-1][j-L[i-1]]のmax
            ll l=max(j-R[i-1], 0LL);
            ll r=max(j-L[i-1]+1, 0LL);
            if(l<r) chmax(dp[i][j], seg.prod(l, r)+V[i-1]);
        }
    }
    if(dp[N][W]<=0) out(-1);
    else out(dp[N][W]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve2();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}