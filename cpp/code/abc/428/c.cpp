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

template<class T> bool chmax(T &a, const T &b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> bool chmin(T &a, const T &b) {
    if (a > b) { a = b; return true; }
    return false;
}

/**
 * stackを2つ使えばいけそうというイメージだけがある
 * 
 * いい括弧列であることの必要十分条件
 * - (を+1, )を-1として累積をスタックに積んだとき, スタックtopが0(バランスが取れている)
 * - 負の値が含まれていない(「)」「(」の順番を排除)
 * 累積と負の値の数を管理して, クエリごとに回答
 * 
 * 折れ線グラフをイメージすると, 上に凸のような形になればよい
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll Q; cin >> Q;
    deque<ll> q;
    ll mcnt=0;
    q.push_back(0);
    rep(qi, 0, Q){
        int op; cin >> op;
        if(op==1){
            char c; cin >> c;
            ll k = q.back()+(c=='(' ? 1 : -1);
            if(k<0)mcnt++;
            q.push_back(k);
        }
        else{
            ll k = q.back(); q.pop_back();
            if(k<0)mcnt--;
        }
        if(q.back()==0 && mcnt<=0) Yes;
        else No;
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