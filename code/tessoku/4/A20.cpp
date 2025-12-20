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
 * dp[i][j]：Sのi(1-indexed)文字目まで, Tのj(1-indexed)文字目まで見たときのSとTの最長共通部分列の長さ
 * ans：dp[sz(S)-1][sz(T)-1]
 * dp[i][j]=max(dp[i][j-1], dp[i-1][j]) when S[i] != T[j]
 * dp[i][j]=max(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]+1) when S[i] == T[j]
 * dp[0][j]とdp[i][0]は0で初期化(片方が0文字で共通部分列を見ようとしても0だから)
 */
void solve() {
    string S, T; cin >> S >> T;
    vvl dp(sz(S)+1, vl(sz(T)+1));
    rep(j, 0, sz(T)+1) dp[0][j]=0;
    rep(i, 0, sz(S)+1) dp[i][0]=0;
    rep(i, 1, sz(S)+1)rep(j, 1, sz(T)+1){
        if(S[i-1]==T[j-1]){
            dp[i][j]=max(dp[i][j-1], max(dp[i-1][j], dp[i-1][j-1]+1));
        }
        else{
            dp[i][j]=max(dp[i][j-1], dp[i-1][j]);
        }
    }
    out(dp[sz(S)][sz(T)]);
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