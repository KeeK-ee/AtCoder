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

const ll INF = 8'000'000'000'000'000'000LL; // 8*10^18
const ll MOD = 998244353;
const ld pi = 3.141592653589793238;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dy4[4] = {-1,0,1,0};
const int dx4[4] = {0,1,0,-1};
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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * 自力AC
 */
// void solve() {
// // ロジックをちゃんと考える！！！
//     ll H, W, N; cin >> H >> W >> N;
//     vl A(N), B(N);
//     set<ll> C, D;
//     rep(i, 0, N) {
//         cin >> A[i] >> B[i]; A[i]--; B[i]--;
//         C.insert(A[i]); D.insert(B[i]);
//     }
//     map<ll, ll> rankA, rankB;
//     ll idx=0;
//     for(ll v : C){
//         rankA[v]=idx; idx++;
//     }
//     idx=0;
//     for(ll v : D){
//         rankB[v]=idx; idx++;
//     }
//     rep(i, 0, N){
//         cout << rankA[A[i]]+1 << " "  << rankB[B[i]]+1 << '\n';
//     }
// }

/**
 * 配列を大小を保ったまま値を小さくする
 * ->座標圧縮
 */
void solve() {
    ll H, W, N; cin >> H >> W >> N;
    vl A(N), B(N), a, b;
    rep(i, 0, N) {
        cin >> A[i] >> B[i]; A[i]--; B[i]--;
        a.push_back(A[i]); b.push_back(B[i]);
    }
    sort(all(a)); sort(all(b));
    a.erase(unique(all(a)), a.end()); b.erase(unique(all(b)), b.end());
    rep(i, 0, N) A[i]=lower_bound(all(a), A[i]) - a.begin();
    rep(i, 0, N) B[i]=lower_bound(all(b), B[i]) - b.begin();

    rep(i, 0, N) cout << A[i]+1 << " " << B[i]+1 << '\n';
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