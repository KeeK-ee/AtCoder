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

ll op(ll a, ll b){
    return max(a, b);
}
ll e(){
    return -INF;
}

/**
 * ナイーブなDP
 * ->dp[i]=max(dp[iまでの直前のK個])+A[i]
 * ->O(N^2)
 * 区間maxを高速に求めたい->セグ木
 * dpの値が毎回変わるため毎回seg.setする
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, K; cin >> N >> K;
    vl A(N); segtree<ll, op, e> seg(N);
    rep(i, 0, N) cin >> A[i];
    vl dp(N, -INF); //dp[i]:石i(1-indexed)に到達するまでに獲得するコインのmax
    dp[0]=A[0];
    rep(i, 0, N){
        if(i==0) seg.set(i, A[0]);
        else seg.set(i, -INF);
    }
    rep(i, 1, N){
        ll mx=seg.prod(max(0LL, i-K), i);
        chmax(dp[i], mx+A[i]);
        seg.set(i, dp[i]);
    }
    out(dp[N-1]);
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