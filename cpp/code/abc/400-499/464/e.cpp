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
 * 最後のクエリで上書きした範囲は必ずそのまま->クエリの逆読みを考える
 * 逆読みに加えて右下から左上にかけてグリッドを見ていく
 * 決まっていない範囲はその文字で上書きしていい
 * 
 * ☆あるマスがすでに決まっていたらそれより左はもう見なくていい(121行目)
 * ☆あるマスがすでにきまっていたらそれより上はもうみなくていい(118行目)
 */
void solve() {
    ll H, W, Q; cin >> H >> W >> Q;
    vvc ANS(H, vc(W, '.'));
    vl R(Q), C(Q);
    vc X(Q);
    rep(qi, 0, Q){
        cin >> R[qi] >> C[qi];
        cin >> X[qi];
    }
    rrep(qi, 0, Q){
        ll r=R[qi]-1, c=C[qi]-1;
        char x=X[qi];
        ll aa=0, bb=r, cc=0, dd=c;
        rrep(i, aa, bb+1){
            if(ANS[i][dd]!='.') break;
            rrep(j, cc, dd+1){
                if(ANS[i][j]=='.') ANS[i][j]=x;
                else{
                    cc=j+1; break;
                }
            }
        }
    }
    rep(i, 0, H){
        rep(j, 0, W){
            if(ANS[i][j]=='.') cout << 'A';
            else cout << ANS[i][j];
        }
        cout << '\n';
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