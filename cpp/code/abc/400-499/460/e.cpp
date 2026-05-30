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
template <typename T> using pq_min = priority_queue<T, vector<T>,greater<T>>; //小さい順

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

ll GetDigit(ll num){
	ll digit = 0;
	while(num != 0){
		num /= 10;
		digit++;
	}
	return digit;
}

/**
 * concatを式で表す
 * x*10^digit(y)+y≡x+y(mod M)
 * x*10^digit(y)≡x(mod M)
 * x(10^digit(y)-1)≡0(mod M)(modだから因数分解できればうれしそうの気持ちで)
 * 場合分け：
 * y自体を全探索しなくてもyの桁数を全探索すれば十分(その桁のyに対するxはすぐに求まりそう)
 * - 10^digit(y)-1がMの倍数：任意のx(<=N)とその桁のyの個数の掛算
 * - そうでない：
 *   - 嘘解法->xがMの倍数だから個数はN/M
 *   - 適切な解法：Mの約数をxと10^digit(y)-1がそれぞれ持っている. g=gcd(M, 10^digit(y)-1)としたときxに必要なのはM/gである. つまりxはM/gの倍数であるから
 * yの個数*N/(M/g)
 * これの総和をmod998でとればいい
 * 
 * ※10^9が登場するためullでないとオーバーフローする
 * ※
 * - E10[i]:10^(i)-1(mod M)
 * - e10[i]:10^(i)
 * のためyの桁数diを固定するとき
 * yはe10[di-1]<=y<e10[di]を満たす(e10[di]~e10[di+1]ではない)
 * Nがdi桁の数かどうかで処理が変わる. lとrをもつのが簡単だと思った(本当に簡単か？)
 */
void solve() {
    ll N, M; cin >> N >> M;
    mint ans=0;
    vector<ull> E10M(20), E10(20);
    ull e=1;
    rep(i, 0, 20){
        E10[i]=e;
        E10M[i]=(e-1+M)%M;
        e*=10;
    }
    ll d=GetDigit(N);
    rep(di, 1, d+1){
        if(E10M[di]==0) {
            mint tmp=0;
            if(E10[di-1]<=N&&N<E10[di]) tmp=(mint)N*(N-E10[di-1]+1);
            else tmp=(mint)N*(E10[di]-E10[di-1]);
            ans+=tmp;
        }
        else{
            mint tmp=0;
            ll g=gcd(E10[di], M);
            ll k=M/g;
            if(E10[di-1]<=N&&N<E10[di]) tmp=(mint)(N/k)*(N-E10[di-1]+1);
            else tmp=(mint)(N/k)*(E10[di]-E10[di-1]);
            ans+=tmp;
        }
    }
    out(ans.val());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}