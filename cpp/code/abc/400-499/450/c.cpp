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

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * グリッドを左上から走査して見たことがない白マスがあればそこからBFSスタート
 * BFSを始めるときのidxの更新を忘れて1ペナ
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];

    vvl idx(H, vl(W, -1));
    vvb  vis(H, vb(W));
    queue<pll> q;

    ll c=1;
    rep(i, 0, H){
        rep(j, 0, W){
            if(S[i][j]=='#'){
                vis[i][j]=true; continue;
            }
            if(vis[i][j]) continue;
            q.push({i, j}); idx[i][j]=c;
            while(!q.empty()){
                auto [y, x]=q.front(); q.pop();
                rep(dir, 0, 4){
                    ll ny=y+dy4[dir], nx=x+dx4[dir];
                    if(outOfGrid(ny, nx, H, W)) continue;
                    if(vis[ny][nx]||S[ny][nx]=='#') continue;
                    vis[ny][nx]=true; q.push({ny, nx});
                    idx[ny][nx]=c;
                }
            }
            c++;
        }
    }

    ll ans=c-1;
    set<ll> s;
    rep(i, 0, H)rep(j, 0, W){
        if(i==0||i==H-1||j==0||j==W-1){
            if(S[i][j]=='.') s.insert(idx[i][j]);
        }
    }
    ans-=sz(s);
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