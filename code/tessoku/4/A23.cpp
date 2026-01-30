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
 * bitDP
 * 商品が無料で変えるかどうかの状態を添え字のビットで判断(=つまりjの状態数が2^N)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vvl A(M, vl(N));
    rep(i, 0, M)rep(j, 0, N) cin >> A[i][j];
    vvl dp(M, vl(1<<N, INF)); //dp[i][j]: i枚目のクーポンまで見たときに, 無料で変える商品の集合が2進数表記でjの時の使用クーポン数の最小値
    dp[0][0]=0;
    ll tmp=0;
    rep(i, 0, N) tmp+=(A[0][i]<<i);
    chmin(dp[0][tmp], 1LL);
    rep(i, 1, M){
        rep(j, 0, (1<<N)){
            //dp[i][j]から配るdp
            ll v=0; //vはjとクーポンi使用可能商品の和集合
            rep(k, 0, N){
                if(((j>>k)&1)||(A[i][k]==1))v+=(1<<k);
            }
            chmin(dp[i][j], dp[i-1][j]);
            chmin(dp[i][v], dp[i-1][j]+1);
        }
    }

    if(dp[M-1][(1<<N)-1]==INF) out("-1");
    else out(dp[M-1][(1<<N)-1]);
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