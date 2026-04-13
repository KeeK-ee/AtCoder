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
 * そもそも穴がない時どうやって数える?
 * ->正方形の1辺の長さごととか考えたけど、、->問題通り「左上座標」と1辺の長さを固定する
 * 穴の数を二次元累積和で数えればよさそう
 * 左上の座標を固定して可能な正方形すべてに対して穴の数==0を満たす個数を数える->O(H*W*(min(H, W)))<=10e10程度でダメ
 * min(H, W)の部分を二分探索で探す(穴が開いている正方形を含む, それより大きい正方形は必ず条件を満たさない)
 * 初期値はl(必ず条件を満たす), r(必ず条件を満たさない)を使用する
 * 添え字ではなく正方形の1辺のlenベースで考えると添え字ガチャガチャしなくて済む
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W, N; cin >> H >> W >> N;
    vvl SUM(H+1, vl(W+1));
    rep(i, 0, N){
        ll a, b; cin >> a >> b;
        SUM[a][b]++;
    }
    rep(i, 0, H+1)rep(j, 1, W+1) SUM[i][j]+=SUM[i][j-1];
    rep(i, 1, H+1)rep(j, 0, W+1) SUM[i][j]+=SUM[i-1][j];

    auto check = [&](ll i, ll j, ll n) -> bool {
        ll cnt=0;
        cnt+=SUM[i+n][j+n];
        cnt+=SUM[i][j];
        cnt-=SUM[i][j+n];
        cnt-=SUM[i+n][j];
        return cnt==0;
    };
    ll ans=0;
    rep(i, 0, H)rep(j, 0, W){
        // 左上を固定
        ll n=min(H-i, W-j)+1;
        // (i, j)~(i+n, j+n)の正方形
        ll l=0, r=n;
        while(r-l>1){
            ll m=(l+r)/2;
            if(check(i, j, m)) l=m;
            else r=m;
        }
        ans+=l;
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