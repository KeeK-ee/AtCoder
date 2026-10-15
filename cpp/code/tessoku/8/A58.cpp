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
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

ll op(ll a, ll b) {return max(a, b);}

ll e() {return -INF;}

/**
 * セグ木
 * 1点更新と区間取得(max)
 * 宣言には型と操作(区間maxであれば、maxを返す二項演算子)と単位元(任意の数と二項演算を行っても元の数が返る数(max演算の単位元は-INF))を使用
 * set(idx, value)
 * prod(l, r) -> 区間l~r-1に対しての操作結果
 */
// void solve() {
// // ロジックをちゃんと考える！！！
//     ll N, Q; cin >> N >> Q;
//     segtree<ll, op, e> seg(N);
//     rep(i, 0, N) seg.set(i, 0);
//     rep(qi, 0, Q){
//         int op; cin >> op;
//         if(op==1){
//             ll pos, x; cin >> pos >> x;
//             pos--;
//             seg.set(pos, x);
//         }
//         else{
//             ll l, r; cin >> l >> r;
//             l--; r--;
//             out(seg.prod(l, r));
//         }
//     }
// }

void solve2(){
    ll N, Q; cin >> N >> Q;
    auto op = [&](ll a, ll b) -> ll {
        return max(a, b);
    };
    auto e = [&]() -> ll { 
        return -INF;
    };
    segtree<ll, op, e> max_seg(N);
    rep(i, 0, N) max_seg.set(i, 0);
    rep(qi, 0, Q){
        int op; cin >> op;
        if(op==1){
            ll pos, x; cin >> pos >> x; pos--;
            max_seg.set(pos, x);
        }
        else{
            ll l, r; cin >> l >> r; l--; r--;
            out(max_seg.prod(l, r));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve2();

    // テストケースが複数ある場合
    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }
    return 0;
}