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
 * 累積max
 * 左からmaxを取るのと右からmaxを取るののmaxというアイデア
 * 右から累積がバグりやすい
 */
// void solve() {
//     ll N; cin >> N;
//     vl A(N);
//     rep(i, 0, N) cin >> A[i];
//     ll D; cin >> D;
//     vl L(D), R(D);
//     rep(i, 0, D){
//         cin >> L[i] >> R[i];
//         L[i]--;R[i]--;
//     }
//     //vL[i](i>=1)：0号室からi-1号室までの累積max
//     vl vL(N+1);
//     rep(i, 1, N+1) vL[i] = max(vL[i-1], A[i-1]);
//     //vR[i](i>=1)：N号室からN-i+1号室までの累積max
//     vl vR(N+1);
//     reverse(all(A));
//     rep(i, 1, N+1) vR[i] = max(vR[i-1], A[i-1]);
//     reverse(all(vR));
//     // rep(i, 0, N+1) cout << vL[i] << " ";
//     // cout << endl;
//     // rep(i, 0, N+1) cout << vR[i] << " ";
//     // cout << endl;
//     rep(i, 0, D){
//         // cout << vL[L[i]] << " " <<  vR[R[i]+1] << " ";
//         out(max( vL[L[i]], vR[R[i]+1]));
//     }
// }

ll op(ll a, ll b) {
    return max(a, b);
}

ll e() {
    return -INF;
}

void solve() {
    ll N; cin >> N;
    segtree<ll, op, e> seg(N);
    rep(i, 0, N) {
        ll a; cin >> a;
        seg.set(i, a);
    }
    ll D; cin >> D;
    rep(i, 0, D){
        ll l, r; cin >> l >> r;
        l--; r--;
        ll x = seg.prod(0, l);
        ll y = seg.prod(r+1, N);
        out(max(x, y));
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