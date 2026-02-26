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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 累積和の配列Cを作るときは
 * C[i][j]=C[i][j-1]+B[j-1]とやればよかった
 * 一度BをCに読み込んでソートしてから累積和をとると0でバグる(負の数が含まれているから0が0項目ではなく変な位置にいってしまう)
 */
// void solve() {
//     // ロジックをちゃんと考える！！！
//     ll N, M; cin >> N >> M;
//     vvl A(N, vl(M));
//     rep(i, 0, N)rep(j, 0, M) cin >> A[i][j];

//     vvl B(M, vl(N));
//     rep(i, 0, M)rep(j, 0, N){
//         B[i][j]=A[j][i];
//     }
//     rep(i, 0, M) sort(all(B[i]));

//     vvl C(M, vl(N+1));
//     rep(i, 0, M)rep(j, 1, N+1) C[i][j]=B[i][j-1];
//     rep(i, 0, M){
//         rep(j, 1, N+1) {
//             C[i][j]+=C[i][j-1];
//         }
//     }

//     ll ans=0;
//     rep(i, 0, M){
//         rep(j, 0, N){
//             ans += (C[i][N]-C[i][j+1])-B[i][j]*(N-j-1);
//         }
//     }
//     out(ans);
// }

/**
 * 全ての非順序対(i, j)に対するabs(B[i]-B[j])の総和
 * ->ソートして各項の寄与を足し合わせる O(N)
 * 寄与=B[i][j]*(j-(N-j-1))=B[i][j]*(2*j-N+1);
 */
void solve() {
    ll N, M; cin >> N >> M;
    vvl A(N, vl(M));
    rep(i, 0, N)rep(j, 0, M) cin >> A[i][j];

    vvl B(M, vl(N));
    rep(i, 0, M)rep(j, 0, N){
        B[i][j]=A[j][i];
    }
    rep(i, 0, M) sort(all(B[i]));

    ll ans=0;
    rep(i, 0, M){
        rep(j, 0, N){
            ans += B[i][j]*(2*j-N+1);
        }
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