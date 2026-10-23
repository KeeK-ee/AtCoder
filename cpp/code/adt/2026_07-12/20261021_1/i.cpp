/**
 * https://github.com/KeeK-ee/AtCoder/tree/main/cpp/mylib
 */

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
#include <cassert>
#include <limits>
#include <bitset>
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

const ll INF = 2'000'000'000'000'000'000LL; // 2*10^18
const ll MOD = 998244353;
const ld PI = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string DIR = "URDL";

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define Yes cout << "Yes" << "\n"
#define No cout << "No" << "\n"
#define out(x) cout << (x) << "\n"
#define fix cout << fixed <<  setprecision(15)

ll ceil_div (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floor_div (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

template <typename T> using pq = priority_queue<T>;
template <typename T> using pq_min = priority_queue<T, Vec<T>, greater<T>>;

ll ll_pow(ll a, ll b) {
    ll res=1;
    rep(i, 0, b) res*=a;
    return res;
}

template <typename T>
void debug_print(const Vec<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        cerr << v[i] << (i == (int)v.size() - 1 ? "" : " ");
    }
    cerr << "\n";
}
template <typename T>
void debug_print(const Vec<Vec<T>>& v) {
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

Vec<mint> fact, inv_fact;

// O(1e6)程度までの前計算
void init_fact(ll N) {
    fact.assign(N+1, 1);
    inv_fact.assign(N+1, 1);
    for (ll i = 1; i <= N; ++i) fact[i] = fact[i-1] * i;
    inv_fact[N] = fact[N].inv();           // ACLのmintはinv()が使える
    for (ll i = N; i >= 1; --i) inv_fact[i-1] = inv_fact[i] * i;
}

mint ncr(ll n, ll r){
    if (r < 0 || r > n || n < 0) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n-r];
}

// O(r)が小さい場合は都度計算する方法もある
mint ncr2(ll n, ll r){
    mint a=1, b=1;
    rrep(i, n-r+1, n+1) a*=i;
    rep(i, 1, r+1) b*=i;
    mint res =  a*(b.pow((ll)(mint::mod())-2));
    return res.val();
}
// 重複組み合わせ: n種類のものからr個選ぶ (順序なし・重複OK)
// nHr = (n+r-1)Cr
// 前提: nCr が定義済み (init_fact 済ませておくこと)
mint nhr(ll n, ll r){
    if (n == 0 && r == 0) return 1;
    if (n <= 0 || r < 0) return 0;
    return ncr(n+r-1, r);
}

// 階乗テーブルを使わない版 (nCr2 を利用)
mint nhr2(ll n, ll r){
    if (n == 0 && r == 0) return 1;
    if (n <= 0 || r < 0) return 0;
    return ncr2(n+r-1, r);
}

/**
 * ufを使いたくなる
 * 連結成分ごとに組み合わせ数を計算して総積を取りそう
 * 例えば ab 1 2はabのみが達成可能でbaは達成できないから、達成できない条件がある
 * ☆"ある"連結成分に対して、同じ文字が2回以上現れるなら、その文字間のswapで任意の回数操作を無駄にできるから、全体として連結成分ごとに任意の並べ替えを達成可能
 * 逆にそうでない(=どの連結成分に対しても同じ文字が高々1回しか現れない)ならば、全体の半分しか達成できない(証明は公式editorialを参照のこと)
 * 
 * 各連結成分ごとの組み合わせ数は(要素数)!/Π((各文字の登場回数)!)(=重複のある順列) https://hiraocafe.com/note/onajimono-jyunretsu.html
 */
void solve() {
    ll N, M; cin >> N >> M;
    string S; cin >> S;
    init_fact(N);
    dsu uf(N);
    mint ans=1;
    Vec<ll> A(M), B(M);
    rep(i, 0, M) {
        cin >> A[i] >> B[i]; A[i]--; B[i]--;
        uf.merge(A[i], B[i]);
    }
    bool d=false;
    for(auto group : uf.groups()){
        Vec<ll> cnt(26);
        for(auto i : group){
            cnt[S[i]-'a']++;
            if(cnt[S[i]-'a']>=2) d=true;
        }
        mint a=0, b=1;
        rep(i, 0, 26){
            a+=cnt[i];
            b*=fact[cnt[i]];
        }
        a=fact[a.val()];
        mint tmp=a/b;
        ans*=tmp;
    }
    if(not d) ans/=2;
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