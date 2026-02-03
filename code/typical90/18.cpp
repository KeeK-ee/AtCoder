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

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(20)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

const long double pi = 3.141592653589793238;

/**
 * 三角関数
 * tanθ=y/xの時, ラジアン表記の角度θ=atan(t, x)で求められる
 * 度数法に直すときは(long double)180.0/piをかければよい
 * 整数のキャスト忘れがないように. 切り捨てられるから
 * 最終的にはdoubleをlong doubleにしたら通った
 */
void solve() {
// ロジックをちゃんと考える！！！
    long double T; cin >> T;
    long double L, X, Y; cin >> L >> X >> Y;

    auto fy = [&](ll E) -> long double {
        long double res = (sin(2*pi*(double)E/T))*(-L/2);
        return res;
    };

    auto fz = [&](ll E) -> long double {
        long double res = L/2 + (cos(2*pi*(double)E/T))*(-L/2);
        return res;
    };

    auto hukaku = [&](long double y, long double z) -> long double {
        long double res = atan2(z, sqrt(X*X+(y-Y)*(y-Y)));
        return res;
    };

    ll Q; cin >> Q;
    rep(qi, 0, Q){
        long double E; cin >> E;
        long double y = fy(E);
        long double z = fz(E);
        long double ans = hukaku(y, z);
        ans *= (long double)180.0/pi;
        fix;
        out(ans);
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