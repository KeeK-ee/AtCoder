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
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

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
 * 上限と下限を管理して更新していく←これは思いついた
 * 各目標に対して達成できる必要十分条件は
 * - 上限が目標の下限以上かつ下限が目標の上限以下(つまり共通領域が存在するということ)
 * ☆新たな上限=min(今の上限, 目標の上限), 新たな下限=max(今の下限, 目標の下限)
 * 全ての目標を達成しながら飛行するから, 仮に目標の上限より上へ行くことができても最も上の高度は目標の上限になる
 * 
 * 存在可能な範囲を管理みたいな
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, H; cin >> N >> H;
    ll up=H, down=H, pre=0;
    bool ok = true;
    rep(i, 0, N){
        ll t, l, u; cin >> t >> l >> u;
        if(up+(t-pre)>=l && down-(t-pre)<=u){
            up = min(u, up+(t-pre));
            down = max(l, down-(t-pre));
            pre = t;
            continue;
        }
        else{
            ok = false;
        }
    }
    if(ok) Yes;
    else No;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}