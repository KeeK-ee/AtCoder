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
#define se second
#define fi first

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
ll ceilDiv (ll x, ll y){if(x >= 0){return (x+y-1)/y;}else{return x/y;}}
ll floorDiv (ll x, ll y){if(x >= 0){return x/y;}else{return (x-y+1)/y;}}

/**
 * N*Nグリッド(i, j)
 * 餌がM-5個, 各餌には色(1~C)がついている
 * 蛇(長さk)はk個の座標と色で表される(尻尾以外の座標は互いに異なる)
 * 
 * 初期状態：
 * 長さ5, 色が全て1(h:head, b:body, t:tail)
 * t............
 * b............
 * b............
 * b............
 * h............
 * .............
 * .............
 *      .
 *      .
 *      .
 * .............
 * 
 * 操作(max:10^5)：
 * - 移動できる, ただしUターンとグリッド外への移動はできない
 * - 移動先に色cの餌があれば, 蛇の長さは1伸びる, 尻尾の色がcになる
 * - 嚙みちぎる, 移動後の頭の位置に胴体がある場合は胴体の位置を尻尾として, その胴体以降がその色の餌に変わる, 移動後は頭と尻尾が座標を共有することになる
 * 
 * 目標：
 * できるだけ短い操作列で好みの色列に近づける
 * 
 * スコア：計算式はよく分からないが, 小さいほど良い
 * 
 * 出力：
 * 操作回数をTとしたときに上下左右に対応する1文字'U', 'D', 'L', 'R'のいずれかをT行出力する
 * 
 * 考察：
 * - 全ての餌を食べると体長がM(好みの色列の長さ)になるから, 最終的に全ての餌を食べるのがよさそう
 * - 操作列は少ない方がいい
 * - 体長を2減らす代わりに色の誤差を1以上減らすことができるならお得
 */

const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
const char dir_char[4] = {'U', 'R', 'D', 'L'};

bool outOfGrid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

void solve() {
    ll N, M, C; cin >> N >> M >> C;
    vl d(M); rep(i, 0, M) cin >> d[i];
    vvl Grid(N, vl(N)); rep(i, 0, N) rep(j, 0, N) cin >> Grid[i][j];
    string ans;

    /**
     * とりあえず蛇行して正のスコアを獲得する
     */
    // auto simpleUpDown = [&]() -> void {
    //     rep(i, 4, N-1) ans+="D";
    //     rep(i, 0, N-1){
    //         ans+="R";
    //         if(i%2==0) rep(j, 0, N-1) ans+="U";
    //         else rep(j, 0, N-1) ans+="D";
    //     }
    // };
    // simpleUpDown();

    auto oneStrokes = [&]() -> void {
        auto evaluate_path = [&](const string& path) -> ll {
            vvl tempGrid=Grid;
            ll current_length=5;
            ll penalty=0;
            int y=4, x=0; // 初期位置

            for(char c : path) {
                if(c == 'U') y--;
                else if(c == 'D') y++;
                else if(c == 'L') x--;
                else if(c == 'R') x++;

                // 餌を食べた場合
                if(tempGrid[y][x] > 0) {
                    if (current_length < M) {
                        // 目標の色との差分をペナルティとして加算
                        penalty += (tempGrid[y][x] != d[current_length]);
                    }
                    current_length++;
                    tempGrid[y][x] = 0; // 餌を消す
                }
            }
            return penalty;
        };

        vs paths;

        // 左から右へ縦ジグザグ
        string path1 = "";
        path1 += string(N-5, 'D');
        rep(i, 0, N-1){
            path1 += "R";
            if(i%2==0) path1 += string(N-1, 'U');
            else path1 += string(N-1, 'D');
        }
        paths.push_back(path1);

        // 上から下へ横ジグザグ
        string path2 = "";
        path2 += string(N-5, 'D');
        path2 += "R";
        path2 += string(N-1, 'U');
        rep(i, 0, N) {
            if (i%2==0) path2 += string(N-2, 'R');
            else path2 += string(N-2, 'L');
            if (i != N-1) path2 += "D";
        }
        paths.push_back(path2);

        // 右から左へ縦ジグザグ
        string path3 = "";
        path3 += string(N-5, 'D');
        path3 += string(N-1, 'R');
        path3+="U";
        rep(i, 0, N-1) {
            if (i % 2 == 0) path3 += string(N-2, 'U');
            else path3 += string(N-2, 'D');
            if (i != N-2) path3 += "L";
        }
        paths.push_back(path3);

        // 下から上へ横ジグザグ
        string path4 = "";
        path4 += string(N-5, 'D');
        path4 += string(N-1, 'R');
        path4 +="U";
        rep(i, 0, N-1) {
            if (i%2==0) path4 += string(N-2, 'L');
            else path4 += string(N-2, 'R');
            if (i != N-2) path4 += "U";
        }
        paths.push_back(path4);

        // 最もペナルティが小さいルートを選択
        ll best_score = INF;

        for(const auto& p : paths) {
            ll score = evaluate_path(p);
            if(score < best_score) {
                best_score = score; ans = p;
            }
        }
    };
    oneStrokes();

    for(auto c : ans) cout << c << "\n";
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