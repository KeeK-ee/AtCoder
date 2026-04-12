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
 * ある頂点を訪問したとき, その状態は
 * - 頂点番号
 * - その時点でのwalkのxor
 * で表される
 * 頂点数:N, xor:2^10(0~2^10-1)のため状態の数はその掛け算
 * 頂点倍加をし1024N頂点でDFSして到達可能性を判定
 * 実際のグラフはN頂点M辺で管理すればよい
 * ☆頂点nでXORがxの頂点はN*1024+xとすればよい
 * ans:頂点N-1を表す1024頂点のうちxor最小
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    const ll X = 1<<10;
    vvpll G(N);
    rep(i, 0, M){
        ll a, b, w; cin >> a >> b >> w; a--; b--;
        G[a].push_back({b, w});
    }

    vb seen(N*X); seen[0]=true;
    
    auto dfs = [&](auto dfs, ll v) -> void {
        ll a=v/X, b=v%X;
        for(auto[to, c] : G[a]){
            if(seen[to*X+(b^c)]) continue;
            seen[to*X+(b^c)]=true;
            dfs(dfs, to*X+(b^c));
        }
    };

    dfs(dfs, 0);
    ll ans=-1;
    rep(i, (N-1)*X, N*X) if(seen[i]) {
        ans=i%X; break;
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