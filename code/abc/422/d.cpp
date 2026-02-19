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
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 余りをバランスよく配分する
 * バランスよく：配列上の左にも右にも寄ることなく配置
 * 操作の最終形態が数列の総和になる&問題で総和Kが与えられるから操作を逆順に行うと数列が構築できそう
 * KをK/2とK+1/2に分割を繰り返す 最後の2^N項が答え
 * K/2とK+1/2の差が必ず1以下だからアンバランスさは0or1を達成可能(K%2^N==0のとき0)
 */
void solve() {
    int N;
    ll K;
    cin >> N >> K;
    vector<ll> dp;

    dp.push_back(K);
    rep(i, 0, N){
        rep(j, 0, 1 << i){
            dp.push_back(dp[(1 << i) - 1 + j]/2);
            dp.push_back(dp[(1 << i) - 1 + j]-dp[(1 << i) - 1 + j]/2);
        }
    }
    ll max=-1, min=2e18;
    rep(i, sz(dp)-(1 << N), sz(dp)) chmax(max, dp[i]), chmin(min, dp[i]);
    out(max-min);
    rep(i, sz(dp)-(1 << N), sz(dp)) cout << dp[i] << " ";
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