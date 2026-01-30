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

ll power(ll a, ll b, ll mod){
    ll p=a, ans=1;
    rep(i, 0, 30){
        if((b>>i)%2) {
            ans *= p;
            ans %= mod;
        }
        p = (p*p) % mod;       
    }
    return ans;
}

/**
 * modの逆元
 * 割り算を含む式のmodを取りなさい→逆元を用いる必要あり！！
 * a/b(mod m)はa*b^m-2 (mod m)に等しい！！(bがmで割り切れないという条件あり)
 * aとbをまず素朴に求めて(modもとってしまう), その後に上の計算をする
 * m-2乗は繰り返し二乗法で
 */
// void solve() {
//     ll n, r; cin >> n >> r;
//     ll a=1, b=1, c=1;
//     rep(i, 1, n+1){
//         a *= i; a %= MOD;
//     }
//     rep(i, 1, r+1){
//         b *= i; b %= MOD;
//     }
//     rep(i, 1, n-r+1){
//         c *= i; c %= MOD;
//     }
//     b = (b*c) %MOD;
//     out(a*power(b, MOD-2, MOD)%MOD);
// }

using mint = modint1000000007;

/**
 * nCr mod を求める関数
 * コンビネーション
 */
mint ncr(ll n, ll r) {
    mint fac_n = 1;
    rep(i, 1, n+1) fac_n *= i;
    mint fac_r = 1;
    rep(i, 1, r+1) fac_r *= i;
    mint fac_nr = 1;
    rep(i, 1, n-r+1) fac_nr *= i;
    mint res = fac_n*((fac_r*fac_nr).pow((mint::mod())-2));
    return res;
}

void solve() {
    ll n, r; cin >> n >> r;
    mint ans = ncr(n, r);
    out(ans.val());

    // mint a=1;
    // rep(i, 1, N+1) a *= i;
    // mint b=1;
    // rep(i, 1, R+1) b *= i;
    // mint c=1;
    // rep(i, 1, N-R+1) c *= i;

    // mint ans = a*((b*c).pow(1000000005));
    // out(ans.val());
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