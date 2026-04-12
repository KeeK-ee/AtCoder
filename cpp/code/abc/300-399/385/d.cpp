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
 * map<ll, set<ll>>は意外と間に合う(?)
 * イテレータを使ったループ内で削除した場合it++で進めようとするとREになる
 * set::eraseは削除した要素の次を指すイテレータを返してくれるので
 * it=xy[sx].erase(it)とするのがよい
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    ll sx, sy; cin >> sx >> sy;

    map<ll, set<ll>> xy, yx;
    rep(i, 0, N){
        ll x, y; cin >> x >> y;
        xy[x].insert(y); yx[y].insert(x);
    }

    ll ans=0;
    rep(m, 0, M){
        char c; cin >> c;
        ll d; cin >> d;
        if(c=='U'){
            // x固定 y=y~y+d
            auto it = xy[sx].lower_bound(sy);
            while(it!=xy[sx].end() && *it<=sy+d){
                yx[*it].erase(sx);
                it=xy[sx].erase(it);
                ans++;
            }
            sy+=d;
        }
        else if(c=='D'){
            // x固定 y=y-d~y
            auto it = xy[sx].lower_bound(sy-d);
            while(it!=xy[sx].end() && *it<=sy){
                yx[*it].erase(sx);
                it=xy[sx].erase(it);
                ans++;
            }
            sy-=d;
        }
        else if(c=='L'){
            // y固定 x=x-d~x
            auto it = yx[sy].lower_bound(sx-d);
            while(it!=yx[sy].end() && *it<=sx){
                xy[*it].erase(sy);
                it=yx[sy].erase(it);
                ans++;
            }
            sx-=d;
        }
        else if(c=='R'){
            // y固定 x=x~x+d
            auto it = yx[sy].lower_bound(sx);
            while(it!=yx[sy].end() && *it<=sx+d){
                xy[*it].erase(sy);
                it=yx[sy].erase(it);
                ans++;
            }
            sx+=d;
        }
    }
    cout << sx << " " << sy << " " << ans << '\n';
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