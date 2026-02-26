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
 * 二次元累積和の基礎
 * 長方形の総和は「右下+左上の1つ左上-右上の上-左下の左」
 */
// void solve() {
//     ll H, W; cin >> H >> W;
//     vector<vl> grid(H, vl(W));
//     rep(i, 0, H)rep(j, 0, W) cin >> grid[i][j];
//     ll Q; cin >> Q;
//     vl A(Q), B(Q), C(Q), D(Q);
//     rep(i, 0, Q) {
//         cin >> A[i] >> B[i] >> C[i] >> D[i];
//         A[i]--;B[i]--;C[i]--;D[i]--;
//     }

//     vector<vl> imos(H+1, vl(W+1));
//     rep(i, 1, H+1)rep(j, 1, W+1) imos[i][j] = imos[i][j-1] + grid[i-1][j-1];
//     rep(j, 1, W+1)rep(i, 1, H+1) imos[i][j] += imos[i-1][j];

//     rep(i, 0, Q){
//         out(imos[A[i]][B[i]]+imos[C[i]+1][D[i]+1]-imos[A[i]][D[i]+1]-imos[C[i]+1][B[i]]);
//     }
// }

void solve() {
    ll H, W; cin >> H >> W;
    vvl grid(H, vl(W));
    rep(i, 0, H)rep(j, 0, W) cin >> grid[i][j];
    vvl sum(H+1, vl(W+1));
    rep(i, 1, H+1)rep(j, 1, W+1) sum[i][j] = sum[i][j-1] + grid[i-1][j-1];
    rep(j, 1, W+1)rep(i, 1, H+1) sum[i][j] += sum[i-1][j];
    ll Q; cin >> Q;
    rep(i, 0, Q){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        out(sum[c+1][d+1]-sum[c+1][b]-sum[a][d+1]+sum[a][b]);
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