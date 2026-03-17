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
 * A, B, Cをそれぞれ1, -1, 0に変換する
 * ->連続部分列で総和が正の(l, r)の組の個数を数えたい
 * ->累積和を取ると, sum[r]-sum[l]>0の(l, r)(0<=l<r<=N)の組の個数
 * ->sum[r]>sum[l]の(l, r)の組の個数
 * ->転倒数の要領でBITでできる sum[i]は負の場合がある BTIではsum[i]の値を添え字にするから全ての要素を+Nする(sumの値は-Nより小さくならないから)
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N; cin >> N;
    string S; cin >> S;
    vl L(N);
    rep(i, 0, N){
        if(S[i]=='A') L[i]=1;
        else if(S[i]=='B') L[i]=-1;
        else L[i]=0;
    }
    vl sumL(N+1);
    rep(i, 1, N+1) sumL[i]=sumL[i-1]+L[i-1];

    fenwick_tree<ll> BIT(3*N);
    ll ans=0;
    rep(i, 0, N+1){
        ll v=BIT.sum(0, sumL[i]+N);
        ans+=v;
        BIT.add(sumL[i]+N, 1);
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