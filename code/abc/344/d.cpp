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

/**
 * 愚直->11^100(i(0~N-1)に対して袋i中の文字のうちどれを使うか(最大10択)or使わない(1択))->ダメ
 * iが小さい方から決まるからDPっぽい
 * dp[i][j](1-indexed):袋iまで見たときにTのj文字目まで一致させるための最小の金額
 * ans:dp[N][sz(T)]
 */
void solve() {
// ロジックをちゃんと考える！！！
    string T; cin >> T;
    ll N; cin >> N;
    vl A(N); vector<vs> S(N);
    rep(i, 0, N){
        ll a; cin >> a; A[i]=a;
        rep(j, 0, a){
            string s; cin >> s;
            S[i].push_back(s);
        }
    }

    vvl dp(N+1, vl(sz(T)+1, INF));
    rep(i, 0, N+1) dp[i][0]=0;

    rep(i, 1, N+1){
        // 袋i-1に対して
        rep(j, 1, sz(T)+1){
            // Tのj-1(0-indexed)文字目までに対して

            // 何もしない
            chmin(dp[i][j], dp[i-1][j]);

            // いずれかを用いる
            rep(k, 0, sz(S[i-1])){
                // S[i-1][k]を用いる
                if(j-sz(S[i-1][k])<0) continue;
                if(S[i-1][k]!=T.substr(j-sz(S[i-1][k]), sz(S[i-1][k]))) continue;
                chmin(dp[i][j], dp[i-1][j-sz(S[i-1][k])]+1);
            }
        }
    }

    if(dp[N][sz(T)]==INF) out(-1);
    else out(dp[N][sz(T)]);
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