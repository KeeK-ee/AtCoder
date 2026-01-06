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
 * p+wの降順にソリを引かせる貪欲法
 * - 全てのトナカイをソリに乗せる
 * - トナカイ1匹にソリを引かせるごとにp[i]+w[i]だけ重さとパワーの差が縮まる
 * - 上の操作を繰り返して, どのトナカイまでソリを引かせればよいか
 * 
 * 数学的な処理に落とし込んで貪欲の正当性を証明する方法もある
 */
void solve() {
    ll N; cin >> N;
    vector<pair<ll, pair<ll, ll>>> p(N);
    rep(i, 0, N) {
        cin >> p[i].second.second >> p[i].second.first;
        p[i].first=p[i].second.second+p[i].second.first;
    }
    ll ans=N, w=0;
    rep(i, 0, N) w += p[i].second.second;
    sort(all(p));
    reverse(all(p));
    ll power=0, idx=0;
    while(power<w){
        power += p[idx].second.first;
        w -= p[idx].second.second;
        ans--;
        idx++;
    }
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}