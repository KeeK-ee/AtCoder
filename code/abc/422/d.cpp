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

    // rep(i, 0, N){
    //     vector<ll> tmp;
    //     for(auto a : ans){
    //         tmp.push_back(a/2);
    //         tmp.push_back(a-a/2);
    //     }
    //     ans = tmp;
    // }
    // ll max = *max_element(all(ans));
    // ll min = *min_element(all(ans));
    // out(max-min);
    // rep(i, 0, sz(ans)) cout << ans[i] << " ";
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