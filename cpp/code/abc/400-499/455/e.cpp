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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * A, B, Cの出現回数が相異なる区間->条件が難しいので否定を考えて全体から引く
 * 否定：「A, B, Cのうち少なくとも2つの出現回数が等しい区間」
 * ->AとBの出現回数が等しい区間+BとCの〃+CとAの〃-2*(AとBとCの〃)(集合3つの包除原理)
 * 
 * AとBの出現回数が等しい区間の数え上げ方法について
 * [l, r)に対してAとBの出現回数が等しいとき
 * Ar-Al=Br-Bl <-> Ar-Br=Al-Bl：これはC問題相当(mapで管理すればO(NlogN)で数えられる)
 * [l, r)に対してAとBとCの出現回数が等しいとき
 * Ar-Al=Br-Bl=Cr-Cl <-> {Ar-Br, Br-Cr}={Al-Bl, Bl-Cl}：これはpairをkeyとしたmapで同様に数えられる
 * 
 * nC2=n*(n-1)/2を利用する
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    string S; cin >> S;

    ll tot=N*(N+1)/2;
    ll cnt=0;

    vl SUMA(N+1), SUMB(N+1), SUMC(N+1);
    rep(i, 0, N){
        if(S[i]=='A') SUMA[i+1]++;
        else if(S[i]=='B') SUMB[i+1]++;
        else SUMC[i+1]++;
    }
    rep(i, 1, N+1) SUMA[i]+=SUMA[i-1];
    rep(i, 1, N+1) SUMB[i]+=SUMB[i-1];
    rep(i, 1, N+1) SUMC[i]+=SUMC[i-1];

    map<ll, ll> ab, bc, ca;
    rep(i, 0, N+1) ab[SUMA[i]-SUMB[i]]++;
    rep(i, 0, N+1) bc[SUMB[i]-SUMC[i]]++;
    rep(i, 0, N+1) ca[SUMC[i]-SUMA[i]]++;
    for(auto[k, v] : ab) cnt+=v*(v-1)/2;
    for(auto[k, v] : bc) cnt+=v*(v-1)/2;
    for(auto[k, v] : ca) cnt+=v*(v-1)/2;

    map<pll, ll> abc;
    rep(i, 0, N+1) abc[{SUMA[i]-SUMB[i], SUMB[i]-SUMC[i]}]++;
    for(auto[k, v] : abc) cnt-=v*(v-1);

    out(tot-cnt);
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