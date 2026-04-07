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
#include <random>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using int128 = __int128_t;
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
#define se second
#define fi first

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

/**
 * やる
 * ABC434-D
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vvl IMOS(2002, vl(2002));
    vl U(N), D(N), L(N), R(N);
    rep(i, 0, N){
        ll u, d, l, r; cin >> u >> d >> l >> r;
        U[i]=u; D[i]=d; L[i]=l; R[i]=r;
        IMOS[u][l]++; IMOS[d+1][r+1]++;
        IMOS[u][r+1]--; IMOS[d+1][l]--;
    }
    rep(i, 0, 2002)rep(j, 1, 2002) IMOS[i][j]+=IMOS[i][j-1];
    rep(j, 0, 2002)rep(i, 1, 2002) IMOS[i][j]+=IMOS[i-1][j];
    ll sum=0;
    vvl ONE(2002, vl(2002));
    rep(i, 1, 2001)rep(j, 1, 2001){
        if(IMOS[i][j]==0)sum++;
        if(IMOS[i][j]==1) ONE[i][j]++;
    }
    rep(i, 0, 2002)rep(j, 1, 2002) ONE[i][j]+=ONE[i][j-1];
    rep(j, 0, 2002)rep(i, 1, 2002) ONE[i][j]+=ONE[i-1][j];
    rep(i, 0, N){
        ll u, d, l, r;
        u=U[i]; d=D[i]; l=L[i]; r=R[i];
        ll cnt=0;
        cnt+=ONE[d][r];
        cnt+=ONE[u-1][l-1];
        cnt-=ONE[d][l-1];
        cnt-=ONE[u-1][r];
        out(sum+cnt);
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