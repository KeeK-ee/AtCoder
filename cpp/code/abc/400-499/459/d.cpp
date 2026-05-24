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

using P = pair<ll, char>;

/**
 * Noである条件：文字数の半分+1以上が同じ文字だとアウト(奇数長の場合は/2の切り上げ+1, 偶数の場合は/2+1)
 * Yesのときどう構築するか
 * (出現数, 文字の種類)のペアを考えて出現数が多いものから貪欲に採用する。その文字を使うごとに出現数をデクリメントする
 * 構築は一個飛ばしとか考えたけど煩雑そう
 */
void solve() {
    // ロジックをちゃんと考える！！！
    string S; cin >> S;
    priority_queue<P> pq_mx;
    map<char, ll> m; for(auto c: S) m[c]++;
    for(auto[f, s] : m) pq_mx.push({s, f});
    
    ll n=pq_mx.top().first;
    if((sz(S)+1)/2+1<=n){ No; return; }

    vc ans(sz(S));
    rep(i, 0, sz(S)){
        auto[cnt1, c1]=pq_mx.top(); pq_mx.pop();
        if(i==0 || (i!=0&&ans[i-1]!=c1)){
            ans[i]=c1; cnt1--;
            if(cnt1>=1) pq_mx.push({cnt1, c1});
            continue;
        }
        auto[cnt2, c2]=pq_mx.top(); pq_mx.pop();
        ans[i]=c2; cnt2--;
        if(cnt2>=1) pq_mx.push({cnt2, c2});
        pq_mx.push({cnt1, c1});
    }
    Yes;
    for(auto c : ans) cout << c;
    cout << '\n';
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