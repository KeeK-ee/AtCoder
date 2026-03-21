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
 * 操作で各Ai mod Kの値は変わらないからKを足しまくることを考えて
 * 最初からAi mod Kをとった後を考えていい
 * その上で「各Aiについて1度だけKを足すことができる. max(A)-min(A)を最小化せよ」という問題を解く
 * AをソートしたときA[N-1]-A[0]は答えの候補の1つ
 * ここで次にKを足したときに答えが改善する可能性のある要素はA[0]
 * 同様にA[1]を最大にしたとき(i=0, 1に+Kしたとき), A[2]を最大にしたとき(i=0, 1, 2に+Kしたとき)....をA[N-1]が最大になる場合までを求めてそのminが答え
 * 
 * mod Kで一番範囲が広い部分をrotateで探す
 * 長さKの円環上で全ての要素が入る区間の最小を探すイメージ
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, K; cin >> N >> K;
    vl A(N);
    rep(i, 0, N) cin >> A[i];

    vl B(N);
    rep(i, 0, N) B[i]=A[i]%K;
    sort(all(B));

    ll ans=B[N-1]-B[0];
    rep(i, 0, N-1){
        chmin(ans, B[i]+K-B[i+1]);
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