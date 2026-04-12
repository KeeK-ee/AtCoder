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
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};

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
 * 縦横の情報をもってBFS
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll H, W; cin >> H >> W;
    vs S(H);
    rep(i, 0, H) cin >> S[i];
    ll sy, sx, gy, gx;
    vector<vvl> dist(H, vvl(W, vl(2, INF)));
    rep(i, 0, H)rep(j, 0, W){
        if(S[i][j]=='S'){
            sy=i; sx=j;
            dist[i][j][0]=0; dist[i][j][1]=0;
        }
        else if(S[i][j]=='G'){
            gy=i; gx=j;
        }
    }
    queue<tuple<ll, ll, int>> q;
    q.push({sy, sx, 0}); q.push({sy, sx, 1});

    while(!q.empty()){
        auto[y, x, p] = q.front(); q.pop();
        rep(i, 0, 4){
            if(i%2 != p) continue;
            ll ny = y + dy[i];
            ll nx = x + dx[i];
            int np = 1 - p;
            if(ny<0 || nx<0 || ny>=H || nx>=W) continue;
            if(S[ny][nx]=='#') continue;
            if(dist[ny][nx][np]<=dist[y][x][p]+1) continue;
            dist[ny][nx][np]=dist[y][x][p]+1;
            q.push({ny, nx, np});
        }
    }

    if(dist[gy][gx][0]==INF && dist[gy][gx][1]==INF) out(-1);
    else out(min(dist[gy][gx][0], dist[gy][gx][1]));
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