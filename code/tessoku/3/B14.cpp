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

#define rep(i, a, n) for (ll i = a; i < (int)(n); ++i)
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
 * 半分全列挙
 * 2^30の計算量をN*2^15に抑える
 * 指数時間の指数部分を半分に抑えることができる
 */
void solve() {
    ll N, K; cin >> N >> K;
    vl A(N), B(N);
    rep(i, 0, N/2) cin >> A[i];
    rep(i, 0, (N+1)/2) cin >> B[i];
    vl a, b;
    rep(i, 0, (1<<(N/2))){
        ll tmp=0;
        rep(j, 0, N)if((i>>j)%2)tmp+=A[j];
        a.push_back(tmp);
    }
    rep(i, 0, (1<<((N+1)/2))){
        ll tmp=0;
        rep(j, 0, N)if((i>>j)%2)tmp+=B[j];
        b.push_back(tmp);
    }
    sort(all(a));sort(all(b));
    rep(i, 0, sz(a)){
        //bにK-a[i]が存在するか？
        auto it = lower_bound(all(b), K-a[i]);
        ll idx = distance(b.begin(), it);
        if(it == b.end()) continue;
        if(b[idx]==K-a[i]){
            Yes;
            return;
        }
    }
    No;
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