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
#define fi first;
#define se second;

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * フェニック木
 * 1点更新(今回は2回)と区間和をともにO(logN)で計算可能
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    fenwick_tree<long long> bit(N);
    vl A(N);
    for (int i = 0; i < N; ++i) {
        long long a;
        cin >> a;
        bit.add(i, a);  // i 番目に a を加算
        A[i]=a;
    }
    // 各クエリ
    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            // スワップクエリ
            long long x;
            cin >> x;
            x--;
            bit.add(x, A[x+1]-A[x]);
            bit.add(x+1, A[x]-A[x+1]);
            swap(A[x], A[x+1]);
        } else {
            // 総和取得クエリ
            int l, r;
            cin >> l >> r;
            l--; r--;
            // 区間 [l, r) の総和を取得して答える
            cout << bit.sum(l, r+1) << endl;
        }
    }
}

// 累積和の解法
//A[x]とA[x+1]をswapしたとき、累積和上で変更されるべきはsumA[x+1](=A[x]のみを含む場所)
//なぜならA[x]+A[x+1]が変わらないからsumA[x+2]以上の場所は不変, またsumA[x]以下の場所は無関係

// void solve(){
//     ll N, Q; cin >> N >> Q;
//     vl A(N);
//     rep(i, 0, N) cin >> A[i];
//     vl sumA(N+1);
//     rep(i, 1, N+1) sumA[i] = sumA[i-1] + A[i-1];
//     rep(qi, 0, Q){
//         int op; cin >> op;
//         if(op==1){
//             ll x; cin >> x; x--;
//             sumA[x+1] = sumA[x] + A[x+1];
//             swap(A[x], A[x+1]);
//         }
//         else{
//             ll l, r; cin >> l >> r; l--; r--;
//             out(sumA[r+1]-sumA[l]);
//         }
//     }
// }

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