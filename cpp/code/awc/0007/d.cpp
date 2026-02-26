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
 * 二次元imos法
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, A, B; cin >> N >> A >> B;
    vvl cnt1(N+1, vl(N+1)), cnt2(N+1, vl(N+1));
    rep(i, 0, A){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        cnt1[a][b]++; cnt1[c+1][d+1]++;
        cnt1[a][d+1]--; cnt1[c+1][b]--;
    }
    rep(i, 0, B){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        cnt2[a][b]++; cnt2[c+1][d+1]++;
        cnt2[a][d+1]--; cnt2[c+1][b]--;
    }
    vvl imos1(N+2, vl(N+2)), imos2(N+2, vl(N+2));
    rep(i, 1, N+2)rep(j, 1, N+2) imos1[i][j] = imos1[i][j-1] + cnt1[i-1][j-1];
    rep(j, 1, N+2)rep(i, 1, N+2) imos1[i][j] += imos1[i-1][j];
    rep(i, 1, N+2)rep(j, 1, N+2) imos2[i][j] = imos2[i][j-1] + cnt2[i-1][j-1];
    rep(j, 1, N+2)rep(i, 1, N+2) imos2[i][j] += imos2[i-1][j];
    ll ans=0;
    rep(i, 1, N+1)rep(j, 1, N+1){
        if(imos1[i][j]>=1 && imos2[i][j]>=1) ans++;
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