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

#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

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
using vc = vector<char>;
using vvc = vector<vc>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;
using bint = cpp_int;

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

/**
 * 嘘解法
 * dp[i][j]:部品iまでを取り付けたときに, 頭の重さがちょうどjであるときの, 嬉しさの合計のmax
 * ans:dp[N][all]のmax
 * ->ロボットを構成する途中でも頭<=体を保つようにしているが, 最終的に頭<=体であればよいだけで過程は関係ないので, この解法は誤り
 * ->正確には誤りではなかった！！ ans:dp[N][w(w<=sum(部品の重さ)-w)]のmax
 * 
 * 全ての部品を体につける
 * 重さWi, 価値Hi-Wiの部品を重さがsum(W)/2を超えないように価値を最大化するよう選ぶ->ナップザックDP
 */
// void solve() {
//     // ロジックをちゃんと考える！！！
//     ll N; cin >> N;
//     vl W(N), H(N), B(N);
//     rep(i, 0, N) cin >> W[i] >> H[i] >> B[i];

//     ll aw=0, bv=0; vl V(N);
//     rep(i, 0, N){
//         aw+=W[i]; V[i]=H[i]-B[i];
//         bv+=B[i];
//     }

//     vvl dp(N+1, vl(aw/2+1, -INF));
//     dp[0][0]=0;

//     rep(i, 1, N+1){
//         rep(j, 0, aw/2+1){
//             dp[i][j]=max(dp[i][j], dp[i-1][j]);
//             if(j-W[i-1]>=0) dp[i][j]=max(dp[i][j], dp[i-1][j-W[i-1]]+V[i-1]);
//             // // 頭につける
//             // if(j-W[i-1]>=0 && j<=w-j) dp[i][j]=max(dp[i][j], dp[i-1][j-W[i-1]]+H[i-1]);
//             // // 体につける
//             // dp[i][j]=max(dp[i][j], dp[i-1][j]+B[i-1]);
//         }
//     }
    
//     ll ans=-INF;
//     rep(i, 0, aw/2+1) chmax(ans, dp[N][i]);
//     out(bv+ans);
// }

void solve() {
    ll N; cin >> N;
    ll aw=0;
    vl W(N), H(N), B(N);
    rep(i, 0, N) {
        cin >> W[i] >> H[i] >> B[i]; aw+=W[i];
    }
    
    const ll w=N*500+2;
    vvl dp(N+1, vl(w, -INF));
    dp[0][0]=0;

    rep(i, 1, N+1){
        rep(j, 0, w){
            // 頭につける
            if(j-W[i-1]>=0) dp[i][j]=max(dp[i-1][j], dp[i-1][j-W[i-1]]+H[i-1]);
            // 体につける
            dp[i][j]=max(dp[i][j], dp[i-1][j]+B[i-1]);
        }
    }

    ll ans=-INF;
    rep(i, 0, w) if(i<=aw-i) chmax(ans, dp[N][i]);
    out(ans);
}

/**
 * 嘘解法の貪欲
 * 体の方の嬉しさが大きいものは体につけるのが最適
 * それ以外を考える
 */
// void solve() {
//     ll N; cin >> N;
//     vl W(N), H(N), B(N);

//     ll aw=0, bw=0, ans=0; vpll m;
//     rep(i, 0, N) {
//         cin >> W[i] >> H[i] >> B[i]; aw+=W[i];
//         if(H[i]<=B[i]) {
//             ans+=B[i]; bw+=W[i];
//             cout << B[i] << " ";
//         }
//         else {
//             m.push_back({H[i]-B[i], i});
//         }
//     }

//     sort(all(m));
//     for(auto [d, idx] : m){
//         if(aw-bw<=bw){
//             ans+=H[idx];
//             cout << H[idx] << " ";
//         }
//         else {
//             // しゃーないときは体につける
//             ans+=B[idx]; bw+=W[idx];
//             cout << B[idx] << " ";
//         }
//     }
//     out(ans);
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