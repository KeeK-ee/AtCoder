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
using pq = priority_queue<ll>;
using pq_min = priority_queue<ll, vector<ll>, greater<ll>>; //小さい順
using mint = modint998244353;

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
bool out_of_grid(ll y, ll x, ll H, ll W) {
    return (y < 0 || x < 0 || y >= H || x >= W);
}

/**
 * imosして雨の日でない日を数える->max(R)=1e18のため無理
 * 座標圧縮とか考えたり、、
 * LRのペアでもってソート, 前から何日種を植えられるか見る
 * pre: 雨が降っていた最後の日
 * cnt: 種を植えた回数
 * pre+1日目に種を植えられない場合のif文で範囲の一方が他方に含まれているパターンでpreが小さくなるバグがある->chmaxで更新する必要あり
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N, M; cin >> N >> M;
    vpll LR(M);
    rep(i, 0, M) {
        cin >> LR[i].first >> LR[i].second;
        LR[i].first--; LR[i].second--;
    }
    if(M==0){
        out(N); return;
    }
    sort(all(LR));
    ll pre=-1, cnt=0;
    rep(i, 0, M){
        if(LR[i].first<=pre+1){
            chmax(pre, LR[i].second);
            continue;
        }
        cnt += LR[i].first-1-pre;
        pre=LR[i].second;
        // cout << "cnt:" << cnt << '\n';
        if(cnt>=N){
            ll ans=LR[i].first-1-(cnt-N);
            out(ans+1); return;
        }
    }
    ll ans=pre+(N-cnt);
    out(ans+1);
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