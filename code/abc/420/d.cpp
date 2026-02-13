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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const int INF = 1000000000; // 1e9, safely within int range
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * スイッチの押下回数（偶奇）によって、盤面は2種類の状態を持つ
 * BFSの盤面を2つ操作する（世界の拡張）
 * スイッチマスに移動するときの処理に注意
 * distの比較でcontinueするときはスイッチの状態sを更新してからでないとダメ
 */
// void solve() {
//     int H, W;
//     cin >> H >> W;
//     vector<string> S(H);
//     rep(i, 0, H) cin >> S[i];

//     int sx, sy, gx, gy;
//     rep(i, 0, H) rep(j, 0, W) {
//         if (S[i][j] == 'S') sx = i, sy = j;
//         if (S[i][j] == 'G') gx = i, gy = j;
//     }

//     int dist[H][W][2];//3つ目はスイッチを押した回数の偶奇（0が偶数）
//     rep(i, 0, H) rep(j, 0, W) rep(k, 0, 2) dist[i][j][k] = INF;
//     dist[sx][sy][0] = 0;
//     queue<tuple<int, int, int>> q;
//     q.push({sx, sy, 0});

//     while (!q.empty()) {
//         auto [x, y, z] = q.front(); q.pop();
//         rep(i, 0, 4) {
//             int nx = x + dx[i];
//             int ny = y + dy[i];
//             int nz = z;
//             if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue; // 範囲外
//             if (S[nx][ny] == '#') continue; // 壁
//             if(nz==0 && S[nx][ny]=='x') continue; //スイッチを偶数回押したとき閉じたドアには進めない
//             if(nz==1 && S[nx][ny]=='o') continue; //スイッチを奇数回押したとき開いたドアには進めない
//             //移動が可能
//             if(S[nx][ny]=='?') nz = 1 - z; // スイッチを押す
//             if(dist[nx][ny][nz] != INF) continue; // すでに訪問済み
//             dist[nx][ny][nz] = dist[x][y][z] + 1;
//             q.push({nx, ny, nz});
//         }
//     }

//     if (dist[gx][gy][0] == INF && dist[gx][gy][1] == INF) out(-1);
//     else out(min(dist[gx][gy][0], dist[gx][gy][1]));
// }

using vs = vector<string>;

void solve() {
    ll H, W; cin >> H >> W;
    vs A(H);
    rep(i, 0, H) cin >> A[i];

    ll sy, sx, gy, gx;
    vector<vector<vector<ll>>> dist(H, vvl(W, vl(2, INF)));
    rep(i, 0, H)rep(j, 0, W){
        if(A[i][j]=='S'){
            sy=i; sx=j;
            dist[i][j][0]=0;
        }
        else if(A[i][j]=='G'){
            gy=i; gx=j;
        }
    }

    queue<tuple<ll, ll, int>> q;
    q.push({sy, sx, 0});
    while(!q.empty()){
        auto [y, x, s] = q.front(); q.pop();
        rep(i, 0, 4){
            ll ny = y + dy[i];
            ll nx = x + dx[i];
            if(ny<0 || nx<0 || ny>=H || nx>=W) continue;
            if(A[ny][nx]=='#') continue;
            if((s%2==0 && A[ny][nx]=='x') || (s%2==1 && A[ny][nx]=='o')) continue;
            ll ns = s;
            if(A[ny][nx]=='?') ns = 1-s;
            if(dist[ny][nx][ns]<=dist[y][x][s]+1) continue;
            dist[ny][nx][ns]=dist[y][x][s]+1;
            q.push({ny, nx, ns});
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