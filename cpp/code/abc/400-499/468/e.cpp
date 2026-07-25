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
#define se second
#define fi first

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

/**
 * 有理数modはp/q=mint(p)/(mint)qで簡単に計算できる
 * 
 * 区間の長さlを固定したときq=lがそろうから分母の総和を求める問題に変形される
 * それぞれの項が何回足されるか？各項の分母への寄与を高速に計算したい
 * N=7で考える lをループさせると各項が足される回数は
 * l=1
 * 1 1 1 1 1 1 1
 * l=2
 * 1 2 2 2 2 2 1
 * l=3
 * 1 2 3 3 3 2 1
 * l=4
 * 1 2 3 4 3 2 1
 * l=5
 * 1 2 3 3 3 2 1
 * l=6
 * 1 2 2 2 2 2 1
 * l=7
 * 1 1 1 1 1 1 1
 * 観察すると各項の寄与は台形のような形になることが分かる
 * - Aの累積和
 * - Aiに対してi+1を掛けたものの累積和(前から1, 2, 3...)
 * - Aiに対してN-iを掛けたものの累積和(後ろから1, 2, 3...)
 * を前計算しておく
 * lに対して適切に区間和を取得することでO(1)(BITはO(logN))で計算可能
 * 
 * 適切な取得について
 * まずはじめに足される回数のmaxを計算しておくmx=min(N-l+1, l);
 * これを利用するとバグが少なく実装可能
 */
void solve() {
    ll N; cin >> N;
    vl A(N); rep(i, 0, N) cin >> A[i];
    
    fenwick_tree<int128> BIT1(N);
    rep(i, 0, N) BIT1.add(i, A[i]);
    vl Fro(N); rep(i, 0, N) Fro[i]=(i+1)*A[i];
    fenwick_tree<int128> BIT2(N);
    rep(i, 0, N) BIT2.add(i, Fro[i]);
    vl Bak(N); rep(i, 0, N) Bak[i]=(N-i)*A[i];
    fenwick_tree<int128> BIT3(N);
    rep(i, 0, N) BIT3.add(i, Bak[i]);

    mint ans=0;
    rep(l, 1, N+1){
        ll mx=min(N-l+1, l);
        mint a=BIT2.sum(0, mx-1);
        mint b=BIT3.sum(N-mx+1, N);
        mint c=(mint)mx*(mint)BIT1.sum(mx-1, N-mx+1);
        mint p=a+b+c;
        mint q=l;
        ans+=p/q;
    }
    out(ans.val());
}

void solve_sumA() {
    ll N; cin >> N;
    vl A(N); rep(i, 0, N) cin >> A[i];
    
    vector<mint> SA(N+1);
    rep(i, 1, N+1) SA[i]=SA[i-1]+A[i-1];
    vector<mint> FA(N+1);
    rep(i, 1, N+1) FA[i]=FA[i-1]+A[i-1]*i;
    vector<mint> BA(N+1);
    rep(i, 1, N+1) BA[i]=BA[i-1]+A[i-1]*(N-i+1);

    mint ans=0;
    rep(l, 1, N+1){
        ll mx=min(N-l+1, l);
        mint a=FA[mx-1]-FA[0];
        mint b=BA[N]-BA[N-mx+1];
        mint c=mx*(mint)(SA[N-mx+1]-SA[mx-1]);
        mint p=a+b+c;
        mint q=l;
        ans+=p/q;
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