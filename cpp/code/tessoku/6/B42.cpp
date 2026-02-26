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
 * 直感的には正に振り切るか負に振り切ればいい？
 * ->表を正負, 裏を正負それぞれに振り切ったとき4パターンを全探索. 
 * スコアが上昇するなら採用して記録
 * ->2種のパラメータをスコアという1次元の値で採用するか判断できてうれしい
 */
void solve() {
    ll N; cin >> N;
    vector<pll> AB(N);
    rep(i, 0, N) cin >> AB[i].first >> AB[i].second;
    vvl scr(2, vl(2));
    vl signFnt = {1, -1};
    vl signBak = {1, -1};
    rep(i, 0, 2)rep(j, 0, 2){
        //表をsignFnt[i], 裏をsignBak[j]に振り切った時にスコアが上昇するか？
        rep(k ,0, N){
            if(AB[k].first*signFnt[i]+AB[k].second*signBak[j]>=1) scr[i][j] += AB[k].first*signFnt[i]+AB[k].second*signBak[j];
        }
    }
    out(max(max(scr[0][0], scr[0][1]), max(scr[1][0], scr[1][1])));
    // out(max({scr[0][0], scr[0][1], scr[1][0], scr[1][1]}));多重max
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