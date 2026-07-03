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
 * 最後が晴れか雨かでDP
 * dp[i][j]:iまで見て, iの天気がj(true:晴れ, false:雨)であるときの達成可能な嬉しさの最大値
 * ans:max(dp[N-1][0], dp[N-1][1])
 * 
 * flipするかどうか2^Nの選択肢があるから余計にDPしたい
 */
void solve() {
    ll N; cin >> N;
    string ts; cin >> ts;
    vb S(N);
    rep(i, 0, N){
        if(ts[i]=='S') S[i]=true;
        else S[i]=false; 
    }
    vl X(N); rep(i, 0, N) cin >> X[i];
    vl Y(N-1); rep(i, 0, N-1) cin >> Y[i];
    vvl DP(N+1, vl(2, -INF));
    DP[0][1]=0; DP[0][0]=0;
    rep(i, 1, N+1){
        // S[i-1]とDP[i-1]を見てDP[i][0 or 1]を決定する

        if(!S[i-1]) {
            chmax(DP[i][0], max(DP[i-1][0], DP[i-1][1]));
            if(i-2>=0)chmax(DP[i][1], max(DP[i-1][1]-X[i-1], DP[i-1][0]-X[i-1]+Y[i-2]));
            else chmax(DP[i][1], DP[i-1][1]-X[i-1]);
        }
        else {
            chmax(DP[i][0], max(DP[i-1][0], DP[i-1][1])-X[i-1]);
            if(i-2>=0) chmax(DP[i][1], max(DP[i-1][1], DP[i-1][0]+Y[i-2]));
            else chmax(DP[i][1], DP[i-1][1]);
        }
    }
    out(max(DP[N][0], DP[N][1]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin >> t;
    while (t--) solve();

    return 0;
}