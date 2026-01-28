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

/**
 * 二次元累積和を思いつく
 * とりあえず, もともとのグリッドに対する累積和を作成
 * (0, 0)~(x, y)の黒ますの総和を求める関数fを作成
 * あとは二次元累積和の計算と同じ要領(右下-右上-左下+左上)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    vs P(N);
    rep(i, 0, N) cin >> P[i];
    vvl grid(N, vl(N));
    rep(i, 0, N)rep(j, 0, N)if(P[i][j]=='B')grid[i][j]=1;
    vvl sum(N+1, vl(N+1));
    rep(i, 1, N+1)rep(j, 1, N+1) sum[i][j]=sum[i][j-1]+grid[i-1][j-1];
    rep(j, 1, N+1)rep(i, 1, N+1) sum[i][j] += sum[i-1][j];
    //sum[i+1][j+1]:(0, 0)~(i, j)の黒ますの総和

    auto f = [&](ll x, ll y) -> ll {
        ll res=0;
        res += (sum[N][N])*(x/N)*(y/N);//一番デカい
        res += (sum[(x%N)][N])*(y/N);
        res += (sum[N][(y%N)])*(x/N);
        res += sum[(x%N)][(y%N)];
        return res;
    };

    rep(i, 0, Q){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        ll ans=f(c+1, d+1)-f(c+1, b)-f(a, d+1)+f(a, b);
        out(ans);
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