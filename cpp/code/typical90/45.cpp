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
 * O(3^N)部分集合の部分集合についてのbitDP
 * dp[bit][j]:bitのグループが確定して, グループ数がjであるときの距離の2乗の最大値の最小値
 */
void solve() {
    ll N, K; cin >> N >> K;
    Vec<int128> X(N), Y(N);
    rep(i, 0, N) {
        ll x, y; cin >> x >> y;
        X[i]=x; Y[i]=y;
    }

    Vec<int128> score(1<<N);
    rep(bit, 0, 1<<N){
        ll mx=0;
        rep(i, 0, N-1)rep(j, i+1, N){
            if((bit>>i)&1 and (bit>>j)&1) chmax(mx, llpow(X[i]-X[j], 2)+llpow(Y[i]-Y[j], 2));
        }
        score[bit]=mx;
    }

    Vec<Vec<int128>> dp((1<<N), Vec<int128>(K+1, INF));
    dp[0][0]=0;
    // rep(i, 0, K+1) dp[0][i]=0;
    rep(bit1, 0, 1<<N){
        for(ll bit2=bit1; bit2>0; bit2=(bit2-1)&bit1){
            rep(k, 0, K+1){
                if(k-1>=0) chmin(dp[bit1][k], max(dp[bit1-bit2][k-1], score[bit2]));
            }
        }
    }

    ll ans=dp[(1<<N)-1][K];
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