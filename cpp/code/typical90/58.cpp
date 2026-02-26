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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

// 各桁の和を計算する関数
ll digit_sum(ll x) {
    ll sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

/**
 * ダブリング
 * 状態遷移が確定的かつ状態数が少なく、遷移回数が非常に多い場合に有効
 * dp[i][j]: 整数jが表示されている状態で2^i回ボタンを押したときに表示されている数
 * i=0は愚直に計算する
 * 2^i回ボタンを押す->2^(i-1)回ボタンを押した後にさらに2^(i-1)回ボタンを押す
 * dp[i+1][j]=dp[i][dp[i][j]]
 * 2^60>10^18よりiは60まででよい
 * 最後に操作回数Kのビットを下から見て更新していく
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, K; cin >> N >> K;
    const ll m=100000;

    vvl dp(60, vl(m));
    rep(i, 0, m){
        dp[0][i]=(i+digit_sum(i))%m;
    }

    rep(i, 0, 60-1){
        rep(j, 0, m){
            dp[i+1][j]=dp[i][dp[i][j]];
        }
    }

    ll cur=N;
    rep(i, 0, 60){
        if((K>>i)&1) cur=dp[i][cur];
    }
    out(cur);
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