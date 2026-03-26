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

// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

// #include <atcoder/all>
// using namespace atcoder;

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
// using mint = modint998244353;
// using bint = cpp_int;

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
 * オフラインでクエリを処理
 * 最後に塗られた色は変わらない
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll H, W, M; cin >> H >> W >> M;
    vl T(M), A(M), X(M);
    rep(i, 0, M) cin >> T[i] >> A[i] >> X[i];

    const int MAX=200005;
    vl cnt(MAX);
    vb fh(H+5), fw(W+5);

    ll h=H, w=W;
    rrep(i, 0, M){
        if(T[i]==1){
            if(!fh[A[i]]){
                cnt[X[i]]+=w;
                fh[A[i]]=true;
                h--;
            }
        }
        else{
            if(!fw[A[i]]){
                cnt[X[i]]+=h;
                fw[A[i]]=true;
                w--;
            }
        }
    }
    
    cnt[0] += h * w;

    vpll ans; // 色, 個数
    rep(i, 0, MAX){
        if(cnt[i]!=0){
            ans.push_back({i, cnt[i]});
        }
    }
    out(sz(ans));
    for(auto [f, s] : ans) cout << f << " " << s << '\n';
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