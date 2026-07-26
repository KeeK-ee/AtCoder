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

bool isPal(const string& s) {
    ll cnt=0;
    for (ll i = 0, j = s.size() ? s.size() - 1 : 0; i < j; ++i, --j) {
        if (s[i] != s[j]) cnt++;
    }
    return cnt<=1;
}

/**
 * 1文字は必ず良い文字列
 * 2文字も必ず良い文字列
 * 3文字も必ず良い文字列
 * 4文字以上は？
 * - 偶数長：前半分と後ろ半分のrevの差が1文字以下
 * - 奇数長：中央を除く〃
 * 
 * 差分更新で判定をO(1)にできる？
 * 偶数長->奇数長
 * 奇数長->偶数長
 * 
 * O(|S|^2)が通るのは間違ってなかった
 * 奇数長と偶数長に分けて(O(|S|))、それぞれに対して中央の1文字or2文字を固定し、左右に伸ばす(O(|S|))ことで全探索(かなり愚直より？)
 * 普段連続部分文字列は左端や右端の固定を考えてしまうけど、それと同じノリで中央を固定を思いつけるか
 */
void solve() {
    string S; cin >> S;
    ll ans=0;

    // 奇数長
    rep(i, 0, sz(S)){
        // 中央の文字(S[i])を固定
        ll l=i, r=i;
        ll cnt=0;
        while(0<=l and r<sz(S)){
            if(S[l]!=S[r]) cnt++;
            if(cnt<=1) ans++;
            else break;
            l--; r++;
        }
    }

    // 偶数長
    rep(i, 0, sz(S)-1){
        // 中央の文字(S[i], S[i+1])を固定
        ll l=i, r=i+1;
        ll cnt=0;
        while(0<=l and r<sz(S)){
            if(S[l]!=S[r]) cnt++;
            if(cnt<=1) ans++;
            else break;
            l--; r++;
        }
    }
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