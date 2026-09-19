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
 * 0があったら0単独で切って良い(怪しい)
 * 0以外はAi<Kより隣の数とくっつけることでKで割り切れるようにできる
 * ソート不可
 * 全探索->切るところを全て試す->O(2^N)->DP?
 * 累積和を取りたくなる？
 * 前から貪欲は流石にダメだよね
 * dp[i][j]:iまでのAの数列であって、Aiがj番目のグループに属するときのスコアの最大値->解けてないわ
 * dp[i][j][k]:iまでのAの数列であって、Aiがj番目のグループに属し, j番目のグループの総和をKで割った余りがkであるときのスコアの最大値->解けてる？O(K*N^2)
 * 
 * 
 * dp[i]:A0~Aiまでを分割したときのスコアの最大値
 * mapの存在判定が必要
 * ZeroSumRanges, 区間スケジューリング
 */
void solve() {
    ll N, K; cin >> N >> K;
    Vec<ll> A(N); rep(i, 0, N) cin >> A[i];
    Vec<ll> sum(N+1); rep(i, 1, N+1) sum[i]=(sum[i-1]+A[i-1])%K;
    Vec<ll> dp(N+1);
    map<ll, ll> m;
    m[0]=0;
    rep(i, 1, N+1){
        // dp[i]を決める
        // A[i-1]をグループの末尾にしない
        chmax(dp[i], dp[i-1]);
        // A[i-1]をグループの末尾にする
        if(m.count(sum[i])) chmax(dp[i], m[sum[i]]+1);
        chmax(m[sum[i]], dp[i]);
    }
    out(dp[N]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}