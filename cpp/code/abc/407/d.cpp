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

const ll INF = 8000000000000000000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};

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
 * ざっくり各マスについてスコアに寄与させるかどうか選んでも2^20~=10^6
 * 実際のドミノの置き方はこれより少ないはずだから全探索でよい
 * ドミノを置かないマスの総xorを計算するのは少しめんどくさいので一度全てのxorを取ってからドミノを置くマスの数をxorで相殺する
 * 各マスにおける選択肢は
 * - ドミノを置かない
 * - ドミノを横向きにおける時に横向きに置く
 * - ドミノを縦向きにおける時に縦向きに置く
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vvl A(H, vl(W));
    ll axor=0;
    rep(i, 0, H)rep(j, 0, W) {
        cin >> A[i][j];
        axor ^= A[i][j];
    }
    ll ans=-INF;
    vvb seen(H, vb(W));
    auto dfs = [&](auto dfs, ll i, ll j, ll x) -> void {
        if(j==W){
            i++; j=0;
        }
        if(i==H){
            chmax(ans, x);
            return;
        }
        //置かない
        dfs(dfs, i, j+1, x);
        //横向き
        if(j<=W-2 && !seen[i][j] && !seen[i][j+1]){
            seen[i][j]=true; seen[i][j+1]=true;
            dfs(dfs, i, j+2, x^A[i][j]^A[i][j+1]);
            seen[i][j]=false; seen[i][j+1]=false;
        }
        //縦向き
        if(i<=H-2 && !seen[i][j] && !seen[i+1][j]){
            seen[i][j]=true; seen[i+1][j]=true;
            dfs(dfs, i, j+1, x^A[i][j]^A[i+1][j]);
            seen[i][j]=false; seen[i+1][j]=false;
        }
    };
    dfs(dfs, 0, 0, axor);
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