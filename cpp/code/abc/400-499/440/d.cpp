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
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;

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
 * 愚直->O(Q*max(Yj)*logN)ダメ
 * リストに含まない数のリストを作る->O(max(Ai)*logN)ダメ
 * XjとXj+Yj-1の間にリストに含まれる数を数えて、あとから足す->最悪ケース(リストが1, 2, 3...3e15でクエリが1, 1の場合はO(Q*N))ダメ
 * 
 * わからん(1/24)
 * 
 * 答えでにぶたん
 * 値をxで固定したときに「xがX[idx]以上の整数であってリストに含まれないもののうち, 小さい方からY[idx]番目以上か？」
 * これを満たす最小値を求める(O(Q*log(max(A))*logN))
 * - X[idx]以上x以下の個数がmx
 * - X[idx]以上x以下のリストに含まれる個数はupper-lower
 * 上-下で個数が分かる
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vl X(Q), Y(Q);
    rep(i, 0, Q) cin >> X[i] >> Y[i];

    sort(all(A));

    auto check = [&](ll x, ll idx) -> bool {
        // xがX[idx]以上の整数であってリストに含まれないもののうち, 小さい方からY[idx]番目以上か？
        if(x<X[idx]) return false;
        ll mx=x-X[idx]+1;
        auto l=lower_bound(all(A), X[idx]);
        auto r=upper_bound(all(A), x);
        return mx-(r-l)>=Y[idx];
    };

    rep(i, 0, Q){
        ll l=-1, r=INF;
        while(r-l>1){
            ll m = (l+r)/2;
            if(check(m, i)) r=m;
            else l=m;
        }
        out(l+1);
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