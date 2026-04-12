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

//#include "../../../ac-library-master/atcoder/dsu.hpp"
//#include <atcoder/all>
//using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;

const ll INF = 1e18;
const ll MOD = 1000000007;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (ll i = (ll)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (ll)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"
#define fix cout << fixed <<  setprecision(10)
#define fi first;
#define se second;

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 各研究者を頂点、利害関係を辺と見ることでグラフに落とし込める
 * 各頂点からの出次数を管理
 * 各研究者に対して、査読者候補がいるとき、その数は候補をnとした時にnC3=n*(n-1)*(n-2)/6
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vl G(N);
    rep(i, 0, M){
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a]++; G[b]++;
    }
    rep(i, 0, N){
        if(N-(G[i]+1)<3) cout << 0 << " ";
        else cout << (N-(G[i]+1))*(N-(G[i]+1)-1)*(N-(G[i]+1)-2)/6 << " ";
    }
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