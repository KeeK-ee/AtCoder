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

// void solve() {
//     ll N; cin >> N;
//     vl A(N), B(N), C(N);
//     rep(i, 0, N) cin >> A[i];
//     rep(i, 0, N) cin >> B[i];
//     rep(i, 0, N) cin >> C[i];
//     vl sumA(N+1), sumB(N+1), sumC(N+1);
//     rep(i, 1, N+1) sumA[i] = sumA[i-1] + A[i-1];
//     rep(i, 1, N+1) sumB[i] = sumB[i-1] + B[i-1];
//     rep(i, 1, N+1) sumC[i] = sumC[i-1] + C[i-1];
//     //-------ここまでは合ってそう-----------
//     vl maxAB(N+2);
//     rep(i, 1, N+2) maxAB[i]=max(maxAB[i-1], sumA[i-1]-sumB[i-1]);
//     ll ans=0;
//     rep(y, 1, N-1){
//         //yを全探索
//         ll tmp=sumB[y+1]-sumC[y+1];
//         // 0<=x<yのにおいてのsumA[x]-sumB[x]の最大値を求める
//         tmp += maxAB[y+1];
//         chmax(ans, tmp);
//     }
//     //-------ここまでも合ってそう-----------
//     ans += sumC[N]; ans -= sumA[0];
//     out(ans);
// }

/**
 * ansは一時的に負になる場合があるから初期値は-INFにしておく
 */
void solve() {
    ll N; cin >> N;
    fenwick_tree<ll> A(N), B(N), C(N);
    rep(i, 0, N) { ll a; cin >> a; A.add(i, a); }
    rep(i, 0, N) { ll b; cin >> b; B.add(i, b); }
    rep(i, 0, N) { ll c; cin >> c; C.add(i, c); }

    ll ans=-INF, mx=-INF;
    rep(y, 1, N-1){
        // yを固定して全探索
        ll tmp=B.sum(0, y+1)-C.sum(0, y+1);
        chmax(mx, A.sum(0, y)-B.sum(0, y));
        chmax(ans, tmp+mx);
    }
    ans+=C.sum(0, N);
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