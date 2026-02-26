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
 * 編集距離(レーベンシュタイン距離)
 * dp[i][j]: Sのi文字目 Tのj文字目まで見たときの編集距離(=挿入, 置換, 削除を行う時の最小手数)
 * dp[i][j]は以下の最小値
 * - dp[i-1][j]+1 (上マスからの遷移で削除に相当する)
 * - dp[i][j-1]+1 (左マスからの遷移で挿入に相当する)
 * - dp[i-1][j-1]+c(if S[i]==T[j] then c=0 else c=1) (左上マスからの遷移で置換に相当する)
 * 
 * https://o-treetree.hatenablog.com/entry/DPL1E
 */
void solve() {
// ロジックをちゃんと考える！！！
    string S, T; cin >> S >> T;
    ll s=sz(S), t=sz(T);
    vvl dp(s+1, vl(t+1));
    rep(j, 0, t+1) dp[0][j]=j;
    rep(i, 0, s+1) dp[i][0]=i;
    rep(i, 1, s+1)rep(j, 1, t+1){
        ll mn = min(dp[i-1][j]+1, dp[i][j-1]+1);
        if(S[i-1]==T[j-1]) chmin(mn, dp[i-1][j-1]);
        else chmin(mn, dp[i-1][j-1]+1);
        dp[i][j]=mn;
    }
    out(dp[s][t]);
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