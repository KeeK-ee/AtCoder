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
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using vc = vector<char>;
using vvc = vector<vc>;
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
#define se second
#define fi first

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
 * 左から決定していく貪欲かと思ったけど違う
 * 反例：
 * 3 2
 * 1 1 1
 * 1 1
 * 正しくは1だが、左から決定すると2になる
 * 
 * 各Aiについてインクリメントは高々1回でOK(2回インクリメントするときはインクリメントしない方がいいから従う)
 * 2^NなのでDPが通りそう
 * dp[i][0 or 1]:iまで見てA[i]をインクリメントした(1)もしくはしない(0)ときの操作回数min
 * ans=max(dp[i][0], dp[i][1])
 * 
 * 実はA0をインクリメントするorしないを決定すると芋ずる式に操作回数が一意に決まるため、2通り計算するだけでOK
 */
void solve() {
    ll N, M; cin >> N >> M;
    vl A(N), B(N-1);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N-1) cin >> B[i];
    vvl dp(N+1, vl(2, INF));
    dp[0][0]=0, dp[0][1]=INF;
    rep(i, 1, N+1){
        // dp[i-1][0 or 1]をみる
        if(i==1){
            dp[i][0]=0; dp[i][1]=1; continue;
        }
        if((A[i-2]+A[i-1])%M==B[i-2]) chmin(dp[i][0], dp[i-1][0]);
        if((A[i-2]+A[i-1]+1)%M==B[i-2]) chmin(dp[i][0], dp[i-1][1]);
        if((A[i-2]+A[i-1]+1)%M==B[i-2]) chmin(dp[i][1], dp[i-1][0]+1);
        if((A[i-2]+A[i-1]+2)%M==B[i-2]) chmin(dp[i][1], dp[i-1][1]+1);
    }
    out(min(dp[N][0], dp[N][1]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}