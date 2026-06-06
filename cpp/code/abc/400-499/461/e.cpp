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
 * クエリ1：
 * - R行目に操作をしたことがなければ+NでOK
 * - 以前に操作をしたことがある場合, 以前のクエリ~今回のクエリまでにクエリ2が何回されたか?(列の重複なし)　その回数分プラス
 * クエリ2：
 * - C行目に操作をしたことがない場合, 最初のクエリ~今回のクエリまでにクエリ1が何回されたか?(行の重複なし)　その回数分マイナス
 * - 以前に操作をしたことがある場合, 以前のクエリ~今回のクエリまでにクエリ1が~~(以下同じ)
 * 
 * クエリの長さをもったBITを使用する
 * 重複なしが難しい. 各行と列に対して以前のクエリの番号をvectorで管理
 * add(pre, -1)してadd(now, 1)とする
 */
void solve() {
    ll N, Q; cin >> N >> Q;
    fenwick_tree<ll> BITR(Q+2), BITC(Q+2);
    vl VR(N+2, -1), VC(N+2, -1);
    ll ans=0;
    rep(qi, 0, Q){
        int op; cin >> op;
        if(op==1){
            ll r; cin >> r; r--;
            if(VR[r]==-1){
                BITR.add(qi, 1);
                ans+=N; VR[r]=qi;
            }
            else{
                BITR.add(VR[r], -1);
                BITR.add(qi, 1);
                ll t=BITC.sum(VR[r], qi);
                ans+=t; VR[r]=qi;
            }
        }
        else{
            ll c; cin >> c; c--;
            if(VC[c]==-1){
                BITC.add(qi, 1);
                ll t=BITR.sum(0, qi);
                ans-=t; VC[c]=qi;
            }
            else{
                BITC.add(VC[c], -1);
                BITC.add(qi, 1);
                ll t=BITR.sum(VC[c], qi);
                ans-=t; VC[c]=qi;
            }
        }
        out(ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while (t--) solve();

    return 0;
}