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
 * ダイクストラ
 * コストの更新の時に頂点のコストを追加して処理
 * 
 * 無向辺を有向辺2つと思って辺のコスト=元の無向辺のコスト+行先のコストとする
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vvpll G(N);
    rep(i, 0, M){
        ll a, b, c; cin >> a >> b >> c; a--; b--;
        G[a].push_back({b, c}); G[b].push_back({a, c});
    }

    vl dist1(N, INF); dist1[0]=A[0];
    priority_queue<pll, vector<pll>, greater<pll>> q1;
    q1.push({A[0], 0}); //{その頂点への現時点の最小コスト, 頂点番号}

    while(!q1.empty()){
        auto [c, to] = q1.top(); q1.pop();
        if(dist1[to]!=c) continue; //確定している
        for(auto [nv, nc] : G[to]){
            if(dist1[nv]<=c+nc+A[nv]) continue; //更新せず
            dist1[nv]=c+nc+A[nv];
            q1.push({dist1[nv], nv});
        }
    }
    rep(i, 1, N) cout << dist1[i] << " ";
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