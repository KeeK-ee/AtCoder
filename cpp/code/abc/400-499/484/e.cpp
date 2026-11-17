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

/**
 * L~Rはf(R)-f(L-1)典型
 * https://atcoder.jp/contests/abc459/tasks/abc459_c
 * みたいに動的な値の追加に対してx以上の要素の個数を求めたい
 * 座圧+セグ木で実装(想定解らしい)
 * treeで殴る(RAINBOUのディスコ)
 */
void solve() {
    ll N, L, R; cin >> N >> L >> R;
    Vec<ll> A(N); rep(i, 0, N) cin >> A[i];
    Vec<ll> sum(N+1); rep(i, 1, N+1) sum[i]=sum[i-1]+A[i-1];
    Vec<ll> zaatu; rep(i, 0, N+1) zaatu.push_back(sum[i]);
    sort(all(zaatu)); zaatu.erase(unique(all(zaatu)), zaatu.end());
    auto f = [&](ll x) -> ll {
        // Aの連続部分列であって、総和がx以下であるものの個数
        ll res=0;
        fenwick_tree<ll> BIT(N+1);
        rep(i, 0, N+1){
            // 右端固定
            // sum[i]-x<=sum[l]なるlの個数
            auto it=lower_bound(all(zaatu), sum[i]-x)-zaatu.begin();
            res+=BIT.sum(it, N+1);
            auto it2=lower_bound(all(zaatu), sum[i])-zaatu.begin();
            BIT.add(it2, 1);
        }
        return res;   
    };
    ll ans=f(R)-f(L-1);
    out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}