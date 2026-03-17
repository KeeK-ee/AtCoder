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
 * x座標は固定しそう
 * このときD<=y<=Uのyについて黒の個数を求める
 * 図から大きく3つの部分に分割できる
 * 1. 黒or白が連続する部分(-abs(x)<=y<=abs(x))
 * 2. 1より上の部分(白黒が交互)
 * 3. 1より下の部分(白黒が交互)
 * それぞれの部分について上端と下端を計算して, 範囲が正であれば数える
 * 2の下端と3の上端が間違いやすい
 * 2の下端はmax(ax+1, D)であってmin(ax, U)+1ではない(具体的な値で考えても一見同じに見えるから間違う、範囲が上の方に振り切った場合を考えると分かる)
 */
void solve() {
    // ロジックをちゃんと考える！！！
    ll L, R, D, U; cin >> L >> R >> D >> U;

    ll ans=0;
    rep(x, L, R+1){
        // x座標をxで固定し, x上の黒を数える
        ll ax=abs(x), tmp=0;

        // 黒or白が連続する区間
        if(ax%2==0) {
            ll u=min(ax, U), d=max(-ax, D);
            if(d<=u) tmp+=(u-d+1);
        }

        // 上端
        {
            ll u=U, d=max(ax+1, D);
            if(d<=u) {
                if((u-d+1)%2==0) tmp+=(u-d+1)/2;
                else {
                    if(u%2) tmp+=(u-d+1)/2;
                    else tmp+=(u-d+2)/2;
                }
            }
        }

        // 下端
        {
            ll u=min(-ax-1, U), d=D;
            if(d<=u) {
                if((u-d+1)%2==0) tmp+=(u-d+1)/2;
                else {
                    if(d%2) tmp+=(u-d+1)/2;
                    else tmp+=(u-d+2)/2;
                }
            }
        }

        ans+=tmp;
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