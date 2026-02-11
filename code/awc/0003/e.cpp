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
 * - sum(W)<=sum(C)
 * - max(W)<=max(C)が必要
 * 各荷物についてどのトラックに入れるか全探索->O(N^M)=15^15->x
 * 貪欲かDP?
 * 貪欲->重い荷物から積載重量の大きいトラックへ入れていく
 * 
 * 数式的にはi=0~N-1に対してCj(j=0~M-1)-=Wiをして
 * Cを負の数にしないように全てのiに対して操作を行いきれるか?
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vl W(N), C(M);
    rep(i, 0, N) cin >> W[i];
    rep(i, 0, M) cin >> C[i];

    sort(all(W)); reverse(all(W));
    sort(all(C)); reverse(all(C));
    rep(i, 0, N){
        if(W[i]>C[0]){
            No; return;
        }
        C[0] -= W[i];
        sort(all(C)); reverse(all(C));
    }
    Yes;
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