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
 * min-max法 後ろから考える
 * 盤面をdp配列で管理
 * dp[i][j]:(i, j)から互いが最善手を打った時のスコア
 * dp[N-1][j] = A[j]
 * iの大きい方から決めていく
 * minをするかmaxをするかはiの偶奇で場合分け
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vvl dp(N, vl(N)); //dp[i][j]: (i, j)状態での互いが最善手を打ったときの最終スコア
    rep(i, 0, N) dp[N-1][i]=A[i];
    rrep(i, 0, N-1){
        rep(j, 0, i+1){
            if(i%2){
                // min
                dp[i][j]=min(dp[i+1][j], dp[i+1][j+1]);
            }
            else{
                // max
                dp[i][j]=max(dp[i+1][j], dp[i+1][j+1]);
            }
        }
    }
    out(dp[0][0]);
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