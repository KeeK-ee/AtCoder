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
 * 直感的に尺取り法を思いついたが実装方法が分からず
 * 
 * 線形で解きたいなーの気持ち
 * まず累積和をとる
 * 始点を固定したときに始点からの合計がM以上となるidx(dとする)をにぶたんで探す
 * i日目~d-1日目=d-iがK以上であれば組(i, j) (j=d-1~N-1)の個数N-d+1を加算
 * d-iがK未満であればi+K-1日目~N-1日目までの組(i, j)の個数N-i-K+1(非負の時のみ)を加算
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, K, M; cin >> N >> K >> M;
    vl A(N);
    rep(i, 0, N) cin >> A[i];
    vl sumA(N+1);
    rep(i, 1, N+1) sumA[i] = sumA[i-1] + A[i-1];

    ll ans=0;
    rep(i, 0, N){
        auto it = lower_bound(all(sumA), sumA[i]+M);
        if(it==sumA.end()) continue;
        ll d = distance(sumA.begin(), it);
        if(d-1-i+1>=K) ans += (N-d+1);
        else ans += (N-i-K+1>=0) ? (N-i-K+1) : 0;
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