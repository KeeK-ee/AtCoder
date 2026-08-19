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
 * ダブリング
 * Y(<=10^9)日後の状態を計算するために各状態(<=N)から2^j日後の状態を
 * dpしておいて, クエリごとにY(日後)の各ビットが立っているかどうかで採用するorしないを繰り返す
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    vl A(N);
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
    }

    vvl dp(32, vl(N)); //dp[j][i]:穴iにいた2^j日後の穴
    rep(i, 0, N) dp[0][i]=A[i];
    rep(j, 1, 32)rep(i, 0, N){
        dp[j][i]=dp[j-1][dp[j-1][i]];
    }

    rep(qi, 0, Q){
        ll x, y; cin >> x >> y;
        x--;
        ll ans=x;
        rrep(i, 0, 32)if((y>>i)&1)ans=dp[i][ans];
        out(ans+1);
    }
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