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
using ull = unsigned long long;
using ld = long double;
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

const ll INF = 1000000000000000000LL; // 10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
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
 * 操作の全探索は無理
 * 感覚的にAとBのdiffを考えそう
 * ☆全てのマスを一度ずつ走査するとき, 4マスの内左上のマスは一度しか操作されないからこれを0にするような貪欲法が最適
 * 一致させることができる必要十分条件は「貪欲をした後に最も右の1列と最もしたの1行が全て0」
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vvl A(H, vl(W)), B(H, vl(W));
    rep(i, 0, H)rep(j, 0, W) cin >> A[i][j];
    rep(i, 0, H)rep(j, 0, W) cin >> B[i][j];
    vvl C(H, vl(W));
    rep(i, 0, H)rep(j, 0, W) C[i][j] = B[i][j] - A[i][j];

    ll ans=0;
    rep(i, 0, H-1)rep(j, 0, W-1){
        ll k = C[i][j]; ans += abs(k);
        C[i][j] -= k; C[i+1][j] -= k; C[i][j+1] -= k; C[i+1][j+1] -= k;
    }

    bool ok=true;
    rep(i, 0, H)if(C[i][W-1] != 0) ok = false;
    rep(j, 0, W)if(C[H-1][j] != 0) ok = false;
    if(ok) {
        Yes; out(ans);
    }
    else No;
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