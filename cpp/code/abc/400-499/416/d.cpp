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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

const ll INF = 1e18;
const int MOD = 1000000007;
const string LOWALP = "abcdefghijklmnopqrstuvwxyz";
const string UPALP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (int i = a; i < (int)(n); ++i)
#define rrep(i, a, n) for (int i = (int)(n) - 1; i >= a; --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define out(x) cout << x << "\n"

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * Ai, Bi<MよりAの大きい要素からBとマッチングさせてMをギリギリ超えるようにすればいい
 * Bの要素に重複の可能性があるからBの要素はmultisetで管理してイテレータで消していく
 * ans = AとBの総和-M*Mを超えたペア数 で計算すると賢い
 * https://atcoder.jp/contests/awc0002/tasks/awc0002_d
 * 上の亜種(重複がないためset上のにぶたんでよい)
 */
void solve() {
    ll N, M; cin >> N >> M;
    vl A(N);
    multiset<ll> s;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        ll b; cin >> b; s.insert(b);
    }
    sort(all(A)); reverse(all(A));
    ll ans=0, cnt=0;
    rep(i, 0, N) ans += A[i]; for(auto v : s) ans += v;
    rep(i, 0, N){
        // A[i]について
        auto it = s.lower_bound(M-A[i]);
        if(it==s.end()) break;
        s.erase(it);
        cnt++;
    }
    out(ans-cnt*M);
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