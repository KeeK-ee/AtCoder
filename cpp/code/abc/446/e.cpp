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
 * まずSnはmod Mで考えて良い
 * ->この時「x, yに対してSn=0となるnが存在するか？」という問題になる
 * また, (i, j)という組を考えたときに数列Sで与えられる遷移は
 * (i, j)->(j, A*j+B*i)となり(i, j)を1つの頂点と見たときにこれは
 * M^2頂点, M^2辺の有効グラフである
 * ->「このグラフ上で(0, x(x=0~M-1))または(x(x=0~M-1), 0)」に到達できないx, yの組を数えたい
 * ->全てのx, yの組からBFSをするのは大変
 * ->(0, x)または(x, 0)からの多始点BFSとして到達性判定をし, 到達できない頂点数が答え
 * 
 * 2つ値を持てば次の遷移が決まる->頂点倍化グラフ
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll M, A, B; cin >> M >> A >> B;
    vvl G(M*M);

    queue<ll> q; vb vis(M*M);
    rep(i, 0, M)rep(j, 0, M){
        ll nv = j*M+(A*j+B*i)%M;
        G[nv].push_back(i*M+j);
        if(i==0||j==0){
            q.push(i*M+j); vis[i*M+j]=true;
        }
        if(j==0||(A*j+B*i)%M==0){
            q.push(nv); vis[nv]=true;
        }
    }

    while(!q.empty()){
        auto v = q.front(); q.pop();
        for(auto to : G[v]){
            if(vis[to]) continue;
            vis[to]=true;
            q.push(to);
        }
    }

    ll ans=0;
    rep(i, 0, M*M) if(!vis[i]) ans++;
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