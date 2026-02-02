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
using mint = modint998244353;

const ll INF = 1e18;
const ll MOD = 998244353;
const string abc = "abcdefghijklmnopqrstuvwxyz";
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1}; // 4近傍、上右下左

#define rep(i, a, n) for (ll i = a; i < (ll)(n); ++i)
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
 * 累積和
 * 1組生徒の成績の累積和は2組生徒の点数を0にしておくと, 学籍番号をそのまま使えて便利←これを思いつかなかったため, 学籍番号->1組だけの配列におけるindexを求めるためににぶたんを使った
 */
void solve() {
// ロジックをちゃんと考える！！！
    ll N; cin >> N;
    vl c1idex, c1pnt, c2idex, c2pnt;
    rep(i, 0, N){
        int c, p; cin >> c >> p;
        if(c==1){
            c1idex.push_back(i);
            c1pnt.push_back(p);
        }
        else{
            c2idex.push_back(i);
            c2pnt.push_back(p);
        }
    }
    vl c1sum(sz(c1pnt)+1), c2sum(sz(c2pnt)+1);
    rep(i, 1, sz(c1pnt)+1) c1sum[i]=c1sum[i-1]+c1pnt[i-1];
    rep(i, 1, sz(c2pnt)+1) c2sum[i]=c2sum[i-1]+c2pnt[i-1];

    ll Q; cin >> Q;
    rep(qi, 0, Q){
        ll l, r; cin >> l >> r;
        l--; r--;
        ll ans1, ans2;
        auto itl1 = lower_bound(all(c1idex), l);
        auto itr1 = upper_bound(all(c1idex), r);
        if(itl1==c1idex.end() || itr1==c1idex.begin()) ans1=0;
        else {
            ll idxl1 = distance(c1idex.begin(), itl1);
            ll idxr1 = distance(c1idex.begin(), itr1-1);
            ans1 = c1sum[idxr1+1]-c1sum[idxl1];
        }

        auto itl2 = lower_bound(all(c2idex), l);
        auto itr2 = upper_bound(all(c2idex), r);
        if(itl2==c2idex.end() || itr2==c2idex.begin()) ans2=0;
        else {
            ll idxl2 = distance(c2idex.begin(), itl2);
            ll idxr2 = distance(c2idex.begin(), itr2-1);
            ans2 = c2sum[idxr2+1]-c2sum[idxl2];
        }

        cout << ans1 << " " << ans2 << '\n';
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