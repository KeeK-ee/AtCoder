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

const ll INF = 1e18;
const ll MOD = 998244353;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 貰うDP(2次元)
 * dp[i][j]: (1, 1)から(i, j)まで行く方法(#マスは0としていい)
 * ans = dp[H-1][W-1]
 * dp[i][j]=dp[i-1][j]+dp[i][j-1](i=0とj=0は注意)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs grid(H);
    rep(i, 0, H) cin >> grid[i];
    vvl dp(H, vl(W));
    dp[0][0]=1;
    rep(i, 0, H)rep(j, 0, W){
        if(grid[i][j]=='#') continue;
        if(i==0&&j==0) continue;
        else if(i==0) dp[i][j]=dp[i][j-1];
        else if(j==0) dp[i][j]=dp[i-1][j];
        else dp[i][j]=dp[i-1][j]+dp[i][j-1];
    }
    out(dp[H-1][W-1]);
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