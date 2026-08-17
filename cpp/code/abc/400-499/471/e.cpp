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
template <typename T> using Vec = vector<T>;
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
const string dir = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, vector<T>, greater<T>>; //小さい順

ll llpow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        debug_print(row);
    }
}

template<class T>
bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T>
bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

vector<mint> fact, inv_fact;

// O(1e6)程度までの前計算
void init_fact(ll N) {
    fact.assign(N+1, 1);
    inv_fact.assign(N+1, 1);
    for (ll i = 1; i <= N; ++i) fact[i] = fact[i-1] * i;
    inv_fact[N] = fact[N].inv();           // ACLのmintはinv()が使える
    for (ll i = N; i >= 1; --i) inv_fact[i-1] = inv_fact[i] * i;
}

mint nCr(ll n, ll r){
    if (r < 0 || r > n || n < 0) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n-r];
}

// O(r)が小さい場合は都度計算する方法もある
mint nCr2(ll n, ll r){
    mint a=1, b=1;
    rrep(i, n-r+1, n+1) a*=i;
    rep(i, 1, r+1) b*=i;
    mint res =  a*(b.pow((ll)(mint::mod())-2));
    return res.val();
}
// 重複組み合わせ: n種類のものからr個選ぶ (順序なし・重複OK)
// nHr = (n+r-1)Cr
// 前提: nCr が定義済み (init_fact 済ませておくこと)
mint nHr(ll n, ll r){
    if (n == 0 && r == 0) return 1;
    if (n <= 0 || r < 0) return 0;
    return nCr(n+r-1, r);
}

// 階乗テーブルを使わない版 (nCr2 を利用)
mint nHr2(ll n, ll r){
    if (n == 0 && r == 0) return 1;
    if (n <= 0 || r < 0) return 0;
    return nCr2(n+r-1, r);
}

/**
 * //本番
 * nCk通り全探索->当然ムリ
 * 各Ai(0-indexed)に対して答えへの寄与を考えそう
 * Aiを必ず採用するとしたときに, Aiが選ばれる組み合わせはn-1-iCk-1通り(重複して数えることを防止している)
 * (x+y)^2=x^2+2xy+y^2
 * Ai^2の配列は使いそうじゃね？
 * 
 * //
 * 
 */
void solve() {
    init_fact(1000005);
    ll N, K; cin >> N >> K;
    Vec<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    mint sum=0;
    rep(i, 0, N) sum+=A[i];
    mint ans=0;
    rep(i, 0, N){
        mint tmp=0;
        // A[i]^2はn-1Ck-1回足される
        tmp+=nCr(N-1, K-1)*A[i]*A[i];
        // A[i][j]はn-2Ck-2回足される
        tmp+=nCr(N-2, K-2)*(sum-A[i])*A[i];
        ans+=tmp;
    }
    out(ans.val());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}