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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const ll INF = 1e18;
const ll MOD = 1000000007;
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
 * dp[i][j]：カードi(0-indexed)まで見ていくつかのカードを選んだ時, 選んだカードに書かれた数の合計をj(1-indexed)にできるか
 * dp[i][j]=(dp[i-1][j])||(dp[i-1][j-A[i]])
 * ans：dp[N-1][S]
 */
void solve() {
    ll N, S; cin >> N >> S;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vector<vector<bool>> dp(N, vector<bool>(10001, false));
    dp[0][0]=true; dp[0][A[0]]=true;
    rep(i, 1, N)rep(j, 0, 10001){
        if(j>=A[i]) dp[i][j]=(dp[i-1][j])||(dp[i-1][j-A[i]]);
        else dp[i][j]=(dp[i-1][j]);
    }
    if(dp[N-1][S])Yes;
    else No;
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