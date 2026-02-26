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
using namespace std;

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
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

const ll INF = 8000000000000000000LL; // 8*10^18
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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * ナイーブにSとGを全探索してそれぞれBFS
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H); rep(i, 0, H) cin >> S[i];

    ll sy=0, sx=0, gy=0, gx=0;
    ll ans=-INF;
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='#') continue;
        else if(S[i][j]=='.'){
            sy=i; sx=j;
        }
        rep(k, 0, H)rep(l, 0, W){
            if(S[k][l]=='#') continue;
            else if(S[k][l]=='.' && !(k==i && l==j)){
                gy=k; gx=l;
            }
            else continue;

            queue<pll> q;
            vvl dist(H, vl(W, INF));
            q.push({sy, sx});
            dist[sy][sx]=0;

            while(!q.empty()){
                auto [y, x]=q.front(); q.pop();
                rep(dir, 0, 4){
                    ll ny=y+dy4[dir], nx=x+dx4[dir];
                    if(out_of_grid(ny, nx, H, W)) continue;
                    if(S[ny][nx]=='#') continue;
                    if(dist[ny][nx]<=dist[y][x]+1) continue;
                    dist[ny][nx]=dist[y][x]+1;
                    q.push({ny, nx});
                }
            }

            chmax(ans, dist[gy][gx]);
        }
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