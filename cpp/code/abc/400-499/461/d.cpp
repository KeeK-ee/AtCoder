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
 * TL4sec制限->500^3(*log500)が通る示唆（見逃した）
 * 二分探索の左端と右端のミス. 両方ともあり得る値の1つ外側にすべき
 * l=lower, r=upperの場合はtmp=r-lでOK(r-1+1ではないよ)
 * 二次元累積和は左だけではなく上にも0の列(行)が必要
 * 
 * O((HW)^2)も通るのアホやろ(3820ms)
 */
void solve() {
    ll H, W, K; cin >> H >> W >> K;
    vs S(H); rep(i, 0, H) cin >> S[i];
    vvl G(H+2, vl(W+2));
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='0') G[i][j]=0;
        else G[i][j]=1;
    }
    vvl SUM(H+2, vl(W+2));
    rep(i, 1, H+2)rep(j, 1, W+2) SUM[i][j]=SUM[i][j-1]+G[i-1][j-1];
    rep(j, 0, W+2)rep(i, 1, H+2) SUM[i][j]+=SUM[i-1][j];
    debug_print(SUM);
    ll ans=0;
    rep(R1, 0, H)rep(R2, R1, H)rep(C2, 0, W){
        ll e, f;
        {
            ll l=-1, r=C2+1;
            while(r-l>1){
                ll m=(r+l)/2;
                ll t=SUM[R1][m]+SUM[R2+1][C2+1]-SUM[R1][C2+1]-SUM[R2+1][m];
                if(t>K) l=m;
                else r=m;
            }
            e=l;
        }
        {
            ll l=-1, r=C2+1;
            while(r-l>1){
                ll m=(r+l)/2;
                ll t=SUM[R1][m]+SUM[R2+1][C2+1]-SUM[R1][C2+1]-SUM[R2+1][m];
                if(t>=K) l=m;
                else r=m;
            }
            f=l;
        }
        ll tmp=f-e;
        ans+=tmp;
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