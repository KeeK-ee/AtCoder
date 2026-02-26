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
 * dp[i]：部屋iに移動するための最短時間
 * dp[i] = min(dp[i-1]+A[i], dp[i-2]+B[i])の漸化式を順番に実行する
 * 
 * dpの復元：後ろから考える
 * dp[i]はi-1から来たのか？i-2から来たのか？遡って保存していく
 */
void solve() {
    ll N; cin >> N;
    vl A(N), B(N);
    rep(i, 1, N) cin >> A[i];
    rep(i, 2, N) cin >> B[i];
    vl dp(N);
    dp[0]=0;
    rep(i, 1, N){
        if(i==1) dp[i] = dp[i-1]+A[i];
        else dp[i] = min(dp[i-1]+A[i], dp[i-2]+B[i]);
    }
    vl ans; ans.push_back(N);
    ll i=N-1;
    while(i>=0){
        if(i==0) break;
        if(i==1) {
            ans.push_back(1);
            i--;
        }
        else if(dp[i]==dp[i-1]+A[i]){
            ans.push_back(i);
            i--;
        }
        else if(dp[i]==dp[i-2]+B[i]) {
            ans.push_back(i-1);
            i-=2;
        }
    }
    reverse(all(ans));
    out(sz(ans));
    rep(i, 0, sz(ans)) cout << ans[i] << " ";
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