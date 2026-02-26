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
 * 愚直=xの全探索は無理
 * xの効用とは？->index上での2*W(つまりWでもある)のラインをずらすことにある
 * つまり1<=x<=Wでよい
 * xの全探索はできるか？->テストケース毎にO(N*W)ダメ
 * xを決めたときに選ぶマスは連続W個で選ぶグループ→選ばないグループを交互に割り当てる
 * 選ぶグループが少ない方がいいのか？->別にそんなことはないから、グループをもとに考えるのは無理そう
 * indexを2*Wで割った余りで分類してはどうか(この発想むずい)
 * 円環として連続W個選んだ部分のコストの総和の最小、テストケース毎にO(N+W)
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, W; cin >> N >> W;
    vl C(N);
    rep(i, 0, N) cin >> C[i];
    vl mod(2*W);
    rep(i, 0, N){
        mod[(i+1)%(2*W)] += C[i];
    }
    // rep(i, 0, 2*W) cout << mod[i] << " ";
    // cout << endl;
    ll ans=INF, tmp=0;
    rep(i, 0, W) tmp+=mod[i];
    chmin(ans, tmp);
    rep(i, 1, 2*W){
        tmp -= mod[i-1];
        tmp += mod[(i+W-1)%(2*W)];
        chmin(ans, tmp);
    }
    out(ans);
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