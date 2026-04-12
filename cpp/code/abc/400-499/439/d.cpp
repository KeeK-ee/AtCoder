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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
using bint = cpp_int;

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

/**
 * jについての制約が厳しいからjを主体に考えそう
 * A[j]が5の倍数でないときは無視
 * A[j]が5の倍数のときAiとAkの値が決まるから組の個数はその掛け算
 * Aを左からmapで個数を管理しながら走査することでjがmaxの場合を
 * 右からの走査でjがminの場合を数える
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl A(N); rep(i, 0, N) cin >> A[i];

    ll ans=0;
    map<ll, ll> m1;
    rep(j, 0, N){
        if(A[j]%5!=0){
            m1[A[j]]++; continue;
        }
        ll Ai=(A[j]/5)*7;
        ll Ak=(A[j]/5)*3;
        ans+=(m1[Ai]*m1[Ak]);
        m1[A[j]]++;
    }
    map<ll, ll> m2;
    rrep(j, 0, N){
        if(A[j]%5!=0){
            m2[A[j]]++; continue;
        }
        ll Ai=(A[j]/5)*7;
        ll Ak=(A[j]/5)*3;
        ans+=(m2[Ai]*m2[Ak]);
        m2[A[j]]++;
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