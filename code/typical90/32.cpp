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

const ll INF = 1e18;
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
 * DFSの解法
 * やっぱりバックトラックって必要なのか
 * 仲が悪い=張らない辺の条件が出てきたからリストは使いにくい->行列を使った
 * DFSの引数の持ち方がやはり慣れていない(終了条件がNなのかN-1なのかとか)
 */
// void solve() {
// // ロジックをちゃんと考える！！！
//     ll N; cin >> N;
//     vvl A(N, vl(N));
//     rep(i, 0, N)rep(j, 0, N) cin >> A[i][j];
//     vvb G(N, vb(N, true));
//     ll M; cin >> M;
//     rep(i, 0, M){
//         ll x, y; cin >> x >> y; x--; y--;
//         G[x][y]=false;
//         G[y][x]=false;
//     }
//     rep(i, 0, N) G[i][i]=false;

//     ll ans=INF;
//     vb seen(N);

//     auto dfs = [&](auto dfs, ll v, ll d, ll c) -> void {
//         if(d==N-1){
//             chmin(ans, c);
//             return;
//         }
//         rep(i, 0, N)if(G[v][i] && !seen[i]){
//             seen[i] = true;
//             dfs(dfs, i, d+1, c+A[i][d+1]);
//             seen[i] = false;
//         }
//     };

//     rep(i, 0, N){
//         rep(j, 0, N) seen[j]=false;
//         seen[i]=true;
//         dfs(dfs, i, 0, A[i][0]);
//     }

//     if(ans==INF) out(-1);
//     else out(ans);
// }

/**
 * N<=10の制約から順列全探索を思いつくべきだった
 * 条件からグラフ->DFSと飛びついてしまった
 */
void solve() {
    ll N; cin >> N;
    vvl A(N, vl(N));
    rep(i, 0, N)rep(j, 0, N) cin >> A[i][j];
    vvb G(N, vb(N, true));
    ll M; cin >> M;
    rep(i, 0, M){
        ll x, y; cin >> x >> y; x--; y--;
        G[x][y]=false;
        G[y][x]=false;
    }
    rep(i, 0, N) G[i][i]=false;
    vl P(N);
    rep(i, 0, N) P[i]=i;
    ll ans=INF;

    do{
        bool ok=true;
        rep(i, 0, N-1){
            if(!G[P[i]][P[i+1]]){
                ok = false;
                continue;
            }
        }
        if(!ok) continue;
        ll tmp=0;
        rep(i, 0, N) tmp += A[P[i]][i];
        chmin(ans, tmp);
    }while(next_permutation(all(P)));

    if(ans==INF) out(-1);
    else out(ans);
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