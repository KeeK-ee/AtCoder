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
 * 残す一色を固定する(3通り). その色について問題が解ければあと2回繰り返すだけでOK
 * - まず達成可能か考える
 * 該当一色以外を同じ数にできればあとはその2色を連打すればいい
 * 最初ボールがc, d, e個とあるする(e個のボールのみにしたい=cとdを同じ数にしたい, 一般にc>dとする)
 * 左2種類に対してd回操作する-> c-d, 0, e+2*d
 * 操作を1回行うごとに中央のボールが2個増えてc-dが1増える->c-dが3の倍数であれば左2つを同じ数にできる
 * 
 * - 次に最小手数を考える
 * おそらくdは0まで減らさなくてもよさそう
 * (c-d)/3回操作をすると左2つが同じ数になる
 * あとは左2つを連打でOK
 */
void solve() {
    vl C(3); rep(i, 0, 3) cin >> C[i];
    ll ans=INF;
    rep(i, 0, 3){
        ll c=C[(i+1)%3], d=C[(i+2)%3], e=C[i];
        if(c<d) swap(c, d);
        if((c-d)%3!=0) continue;
        ll tmp=0;
        tmp+=c%3;
        c-=c%3; d-=c%3; e+=2*(c%3);
        ll f=(c-d)/3;
        tmp+=f;
        c-=f; d+=2*f; e-=f;
        tmp+=c;
        chmin(ans, tmp);
    }
    if(ans==INF) out(-1);
    else out(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin >> t;
    while (t--) solve();

    return 0;
}