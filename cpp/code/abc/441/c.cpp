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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 愚直->酒が入っているnCkのパターンの列挙->計算量分からんけど無理そう
 * まず、可能か不可能かを判定できるか？
 * -> Xがめちゃくちゃ大きい場合は不可能そう
 * -> 不可能な場合, Xをどこまで小さくできるか？
 * -> 最悪ケースはAの下からK個に酒が入ったパターン-> {Aの下からK個のsum}<Xで-1
 * 逆に{Aの下からK個のsum}>=Xの時, 最悪全てのカップの液体を飲むことで目標を達成できるから, {Aの下からK個のsum}<X =>"-1"は必要十分
 * 次に可能な場合のansを求めたい
 * 「どのカップに日本酒が入っているかによらず」->条件がきついため, 必要条件から考えたい感覚がある
 * 最悪ケースは量が少ないAのK個に酒が入っている場合
 * また, 水が入っているN-K個のカップは必ず選ぶとしてよい
 * (ここでつまづいた！！)高橋くんからすれば、量の多いカップから優先して選ぶのが"最適"だから、最悪ケースではAの小さい方からK番目からindexをデクリメントしていって順に足す(量が多い方から選ぶような貪欲法). X以上になった時点でそれまでの個数とN-Kを足したものが答え
 * (ちなみに)問題文に"また、高橋くんがどのようなカップの選び方をしても"とあればAの小さい方から選んで足してX以上までが正当
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, K; cin >> N >> K;
    ll X; cin >> X;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    sort(all(A));
    ll tmp=0;
    rep(i, 0, K) tmp+=A[i];
    if(tmp<X){
        out("-1");
        return;
    }
    ll ans=0;
    tmp=0;
    rrep(i, 0, K){
        tmp += A[i];
        ans++;
        if(X<=tmp)break;
    }
    ans += (N-K);
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