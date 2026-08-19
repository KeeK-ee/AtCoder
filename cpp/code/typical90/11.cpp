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
 * スケジュール->締め切りの早い順に採用することが常に最適
 * dp[i][j]:i番目の仕事まで見て, ちょうどj日目の終わりまで経過したときの獲得報酬のmax
 * あとは割とシンプルなDP
 */
void solve() {
    ll N; cin >> N;
    Vec<tuple<ll, ll, ll >> data(N);
    rep(i, 0, N){
        ll d, c, s; cin >> d >> c >> s;
        data[i]={d, c, s};
    }
    sort(all(data));

    Vec<Vec<ll>> dp(N+1, Vec<ll>(5001));
    rep(i, 1, N+1){
        rep(j, 0, 5001){
            // dp[i][j]を決定する
            auto [d, c, s]=data[i-1];

            // i番目の仕事を受けない
            chmax(dp[i][j], dp[i-1][j]);

            // i番目の仕事を受ける
            if(j<=d and j-c>=0) chmax(dp[i][j], dp[i-1][j-c]+s);

        }
    }

    ll ans=0;
    rep(i, 0, 5001) chmax(ans, dp[N][i]);
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