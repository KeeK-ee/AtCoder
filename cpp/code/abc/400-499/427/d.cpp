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
 * dp[i][j]:合わせてi回操作を行った後, 駒が頂点jにいる状態からスタートして最適な行動をとったとき, Aliceが勝つかどうか
 * ans:dp[0][0]
 * 後ろからDPしていく
 * 初期値:dp[2*K][i]->S[i]=='A'に等しい
 * dp[i][j]はiが偶数のときAlice, 奇数のときBobの最適な行動を考える
 * ぐ: jからの遷移先toでdp[i+1][to]=true(Aliceの必勝)があればtrue
 * き: jからの遷移先toでdp[i+1][to]=false(Bobの必勝)があればfalse
 * 
 * ゲームの先手後手必勝->後ろから考えがち
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll N, M, K; cin >> N >> M >> K;
    string S; cin >> S;
    vvl G(N);
    rep(i, 0, M){
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v);
    }
    rep(i, 0, N) sort(all(G[i]));

    vvb dp(2*K+1, vb(N));
    rep(i, 0, N) dp[2*K][i]=(S[i]=='A');
    rrep(i, 0, 2*K){
        rep(j, 0, N){
            if(i%2){
                // Bob
                bool ok=false;
                for(auto to : G[j]){
                    if(!dp[i+1][to]) ok=true;
                }
                dp[i][j]=!ok;
            }
            else{
                // Alice
                bool ok=false;
                for(auto to : G[j]){
                    if(dp[i+1][to]) ok=true;
                }
                dp[i][j]=ok;
            }
        }
    }

    if(dp[0][0]) out("Alice");
    else out("Bob");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    // solve();

    // テストケースが複数ある場合
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}