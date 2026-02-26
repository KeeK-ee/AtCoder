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

#include <atcoder/all>
using namespace atcoder;

using ll = long long;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vs = vector<string>;
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順

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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * 数学的問題
 * x*xはDにできるだけ近づけてよいか？
 * ->そんなことはない
 * ex)8^2+15^2=17^2である. D=17とみなしたとき, xは16でなく15が最適
 * つまりx, yがともに中途半端(どちらかを限界まで大きくすればいいという話ではない)な場合が存在する
 * 
 * D<=2^10^12よりO(sqrt(D))は間に合う
 * ->xをx*xがDをはじめて超えるまでの範囲で全探索(=固定)したくなる
 * x*x-D>=0のとき: y=0が最適
 * x*x-D<0のとき: yはsqrt(D-x*x)の整数部分orそれ+1のどちからが最適
 * 整数部分の取得はキャストすればいい
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll D; cin >> D;
    ll ans = INF;
    for(ll x=0; x*x<=D; x++){
        if(x*x-D>=0){
            chmin(ans, x*x-D);
        }
        else{
            double tmp = sqrt(D-x*x);
            ll tmp2 = (ll)tmp;
            ll tmp3 = tmp2+1;
            chmin(ans, D-x*x-tmp2*tmp2);
            chmin(ans, x*x+tmp3*tmp3-D);
        }
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