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
 * 区間スケジューリングの応用
 * 基本的にRが小さい車から優先して駐車したい
 * 各駐車スペースに対して, ここから駐車できる車のRをpush(以前のものも残しておく)
 * Rが最も小さいものをpri queueで取得する
 * Rが今見ている駐車枠以前であれば駐車不能
 * 
 * 最後の判定はqueueが空であるとするか駐車した車をカウントしておいてMに一致するか
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    if(N<M){
        No; return;
    }
    vvl car(N);
    rep(i, 0, M) {
        ll l, r; cin >> l >> r; l--; r--;
        car[l].push_back(r);
    }
    pq_min q;
    ll cnt=0;
    rep(i, 0, N){
        rep(j, 0, sz(car[i])) q.push(car[i][j]);
        if(!q.empty() && q.top()<i){
            No; return;
        }
        if(!q.empty()){
            q.pop(); cnt++;
        }
    }
    if(cnt==M){
        Yes; return;
    }
    else No;
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