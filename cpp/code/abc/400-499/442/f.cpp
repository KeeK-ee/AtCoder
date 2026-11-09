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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
using ld = long double;
using pll = pair<ll, ll>;
template <typename T> using Vec = vector<T>;
using mint = modint998244353;

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

/**
 * BITとセグ木間に合わない～泣泣
 */
void solve() {
    ll N; cin >> N;
    Vec<Vec<ll>> S(N, Vec<ll>(N));
    rep(i, 0, N){
        string s; cin >> s;
        rep(j, 0, N){
            if(s[j]=='#') S[i][j]=1;
        }
    }
    
    Vec<Vec<ll>> sum_b(N, Vec<ll>(N+1));
    rep(i, 0, N){
        rep(j, 1, N+1) sum_b[i][j]=sum_b[i][j-1]+S[i][j-1];
    }
    Vec<Vec<ll>> sum_w(N, Vec<ll>(N+1));
    rep(i, 0, N){
        rrep(j, 0, N) sum_w[i][j]=sum_w[i][j+1]+(1-S[i][j]);
    }
    // debug_print(sum_b);
    // debug_print(sum_w);
    /**
     * dp[i][j]:i行目まで見て, 左からj列分が白く塗られたときの操作回数min
     */
    Vec<Vec<ll>> dp(N, Vec<ll>(N+1, INF));
    rep(i, 0, N){

        Vec<ll> mn(N+1);
        if(i!=0){
            rep(j, 0, N+1) mn[j]=dp[i-1][j];
            rrep(j, 0, N) mn[j]=min(mn[j], mn[j+1]);
        }
        // debug_print(mn);

        rep(j, 0, N+1){
            /*
            dp[i][j]=BIT_B[i].sum(0, j)+BIT_W[i].sum(j, N)+min_seg.prod(j, N+1);
            */
            // dp[i][j]を決める
            if(i==0) dp[i][j]=sum_b[i][j]+sum_w[i][j];
            else {
                dp[i][j]=sum_b[i][j]+sum_w[i][j]+mn[j];
            }
        }
    }

    ll ans=INF;
    rep(i, 0, N+1) chmin(ans, dp[N-1][i]);
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