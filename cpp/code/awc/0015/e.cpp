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
 * Mo'sアルゴリズムかBITで解く
 * 
 * 以下Geminiより
 * 解法のコアアイデア：
 * 「先読み（オフラインクエリ）」＋「右端管理」「種類数」を数えるときの最大の壁は、「同じ花が複数回出てきたら1回だけ数えたい」という点です。これを解決するために、以下のルールで配列を管理します。
 * - クエリを $R$（右端）が小さい順に処理する（先読み）。
 * - 左から順番に花を見ていき、「同じ花が出たら、昔の位置のカウントを消して、今の位置に $+1$ を付け直す」。
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, Q; cin >> N >> Q;
    vl P(N); rep(i, 0, N) cin >> P[i];

    vvpll q(N);
    rep(i, 0, Q){
        ll l, r; cin >> l >> r; l--; r--;
        q[r].push_back({l, i});
    }

    vl ans(Q);
    fenwick_tree<ll> BIT(N);
    vl last(N+1, -1);

    rep(i, 0, N){
        ll v=P[i];
        if(last[v]!=-1){
            BIT.add(last[v], -1);
        }
        BIT.add(i, 1);
        last[v]=i;
        for(auto [l, idx] : q[i]){
            ans[idx]=BIT.sum(i, i+1);
        }
    }

    for(auto v : ans) out(v);
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