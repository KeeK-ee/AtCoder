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
 * 全探索する対象の工夫
 * 純粋な2^Nの全探索は不可能
 * 体力の幅と気力の幅を全探索：10^4
 * 各幅に対して, 生徒iが参加できるかの判定：N=3*10^2
 * 全体として10^6程度の計算で間に合う
 */
void solve() {
    ll N, K; cin >> N >> K;
    vector<pll> AB(N);
    rep(i, 0, N) cin >> AB[i].first >> AB[i].second;
    ll ans=0;
    rep(i, 1, 100-K+1)rep(j, 1, 100-K+1){
        //体力がi~i+KまでOK, 気力がj~j+KまでOK
        ll cnt=0;
        rep(k, 0, N)if((i<=AB[k].first && AB[k].first<=i+K)&&(j<=AB[k].second && AB[k].second<=j+K))cnt++;
        chmax(ans, cnt);
    }
    out(ans);
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