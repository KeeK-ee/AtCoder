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
 * トポロジカルソート, DAG(Directed Acyclic Graph)判定(O(NlogN))
 * DAGの判定:入次数0の頂点が存在するので, それを取って消す. それを繰り返して頂点が無くなるか->実装上は選んだ順にansに入れていって, sz(ans)!=Nなら不可
 * 辞書順最小：入次数0の頂点の中で番号が小さいものから貪欲に取る->priority_queueが使える
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vvl G(N);
    vl deg(N); //入次数のカウンター
    rep(i, 0, M){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        deg[b]++;
    }
    pq_min q;
    vl ans;
    rep(i, 0, N)if(deg[i]==0)q.push(i);
    while(!q.empty()){
        auto v = q.top(); q.pop();
        ans.push_back(v);
        for(auto to : G[v]){
            deg[to]--;
            if(deg[to]==0)q.push(to);
        }
    }
    if(sz(ans)!=N) out(-1);
    else {
        rep(i, 0, sz(ans)) cout << ans[i]+1 << " ";
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