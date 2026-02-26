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

const ll INF = 1000000000000000000LL; // 10^18
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
#define fix cout << fixed <<  setprecision(10)

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 数列を実際にシフトするのは無駄
 * シフト量を管理して, クエリで与えられた添え字をうまく変形する
 */
// void solve() {
// // ロジックをちゃんと考える！！！
//     ll N, Q; cin >> N >> Q;
//     vl A(N);
//     rep(i, 0, N) cin >> A[i];
//     ll sft=0;
//     rep(qi, 0, Q){
//         int op; cin >> op;
//         ll x, y; cin >> x >> y;
//         if(op==1){
//             x--; y--;
//             x = (x-sft<0 ? (x-sft+N)%N : x-sft);
//             y = (y-sft<0 ? (y-sft+N)%N : y-sft);
//             swap(A[x], A[y]);
//         }
//         else if(op==2){
//             sft++;
//             sft %= N;
//         }
//         else{
//             x--;
//             x = (x-sft<0 ? (x-sft+N)%N : x-sft);
//             out(A[x]);
//         }
//     }
// }

void solve() {
    ll N, Q; cin >> N >> Q;
    deque<ll> q;
    rep(i, 0, N){
        ll a; cin >> a;
        q.push_back(a);
    }
    rep(qi, 0, Q){
        int op; cin >> op;
        ll x, y; cin >> x >> y;
        if(op==1){
            x--; y--;
            swap(q[x], q[y]);
        }
        else if(op==2){
            ll a = q.back(); q.pop_back();
            q.push_front(a);
        }
        else{
            x--;
            out(q[x]);
        }
    }
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