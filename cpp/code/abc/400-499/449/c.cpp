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
 * 文字ごとの累積和をとる
 * 添え字ガチャをしなければならなかった
 */
// void solve() {
//     // ロジックをちゃんと考える！！！
//     ll N, L, R; cin >> N >> L >> R;
//     string S; cin >> S;
//     vvl sum(26, vl(N+2));
//     rep(i, 0, N){
//         sum[S[i]-'a'][i+1]++;
//     }
//     rep(i, 0, 26){
//         rep(j, 1, N+2){
//             sum[i][j]+=sum[i][j-1];
//         }
//     }
//     ll ans=0;
//     rep(i, 0, N){
//         ll l = min(i+L, N);
//         ll r = min(i+R+1, N);
//         if(l>=r) continue;
//         ll tmp = sum[S[i]-'a'][r]-sum[S[i]-'a'][l];
//         ans += tmp;
//     }
//     out(ans);
// }

/**
 * mapで文字の出現回数をカウントする
 * 両端を差分更新する
 */
// void solve() {
//     ll N, L, R; cin >> N >> L >> R;
//     string S; cin >> S;

//     map<char, ll> m;
//     rep(i, L, R+1) m[S[i]]++;

//     ll ans=0;
//     rep(i, 0, N){
//         ans+=m[S[i]];
//         if(L+i<N) m[S[L+i]]--;
//         if(R+i+1<N) m[S[R+i+1]]++;
//     }
//     out(ans);
// }

/**
 * フェニック木
 */
// void solve() {
//     ll N, L, R; cin >> N >> L >> R;
//     string S; cin >> S;

//     vector<fenwick_tree<ll>> cnt(26, fenwick_tree<ll>(N));
//     rep(i, 0, N) cnt[S[i]-'a'].add(i, 1);

//     ll ans=0;
//     rep(i, 0, N){
//         ll l=min(i+L, N), r=min(i+R+1, N);
//         if(l>=r) continue;
//         ans += cnt[S[i]-'a'].sum(l, r);
//     }
//     out(ans);
// }

/**
 * 文字ごとのidxを管理
 * にぶたんでi+Lからi+Rの個数を計算
 */
void solve() {
    ll N, L, R; cin >> N >> L >> R;
    string S; cin >> S;

    vvl idx(26);
    rep(i, 0, N) idx[S[i]-'a'].push_back(i);

    ll ans=0;
    rep(i, 0, N){
        ll c=S[i]-'a';
        auto l=lower_bound(all(idx[c]), i+L);
        auto r=upper_bound(all(idx[c]), i+R);
        ans+=r-l;
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