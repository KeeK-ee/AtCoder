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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * 訪問順15!の全探索は不可能
 * Sからマンハッタン距離の近い順に訪問する貪欲しか思いつかなかったため実装
 * ->30WA/79
 * (本当は良くないが)M=15から2^15->bitDPではないか?
 * ->でも, 荷物の集合だけ管理しても, 次に荷物を回収するコストは「今どこにいるか次第」では?
 * 解説によるとdp[i][j]: 荷物の集合iを訪問し, 最後に荷物jの場所にいるときの最小移動距離
 * dpの初期状態は(sy, sx)から直接向かう場合M通り
 * 矛盾する場合は適宜continue要
 * 
 * 状態数M*2^Mで遷移にMかかるため全体でO(M^2*2^M)
 * 
 * M=0のときだけコーナーなので特別扱い
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    ll S, T; cin >> S >> T; S--; T--;
    ll sy=S/N, sx=S%N, gy=T/N , gx=T%N;
    if (M==0) {
        out(abs(sy-gy)+abs(sx-gx));
        return;
    }
    vpll P(M); 
    rep(i, 0, M) {
        ll p; cin >> p; p--;
        P[i].first=p/N; P[i].second=p%N;
    }

    vvl dp((1<<M), vl(M, INF));
    rep(i, 0, M) dp[(1<<i)][i]=abs(sy-P[i].first)+abs(sx-P[i].second);
    
    rep(i, 0, (1<<M)){
        rep(j, 0, M){
            // dp[i][j]からの遷移について
            if(!((i>>j)&1)) continue; // iにjが含まれていないならスキップ
            if(dp[i][j]==INF) continue; // dp[i][j]=INFなら遷移しない
            rep(k, 0, M){
                if((i>>k)&1) continue; // iにkが含まれているならスキップ
                chmin(dp[i|(1<<k)][k], dp[i][j]+abs(P[j].first-P[k].first)+abs(P[j].second-P[k].second));
            }
        }
    }

    ll ans=INF;
    rep(i, 0, M) chmin(ans, dp[(1<<M)-1][i]+abs(gy-P[i].first)+abs(gx-P[i].second));
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