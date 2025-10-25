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

void solve() {
    ll N, M, C; cin >> N >> M >> C;
    map<ll, ll> m; //座標, そこの人数
    rep(i, 0, N){
        ll a; cin >> a;
        m[a]++;
    }

    ll cnt=0;
    vector<ll> sum;
    for(auto [k, v] : m){
        sum.push_back(cnt);
        cnt+=v;
    }
    sum.push_back(cnt);

    ll ans=0;
    ll prek=(*m.rbegin()).first;
    ll idx=0;
    for(auto [k, v] : m){
        //座標k, 人数vからスタート
        //kの累積和+Cでにぶたん, lower
        auto it_lower = lower_bound(sum.begin(), sum.end(), sum[idx]+C);
        ll idx_lower = distance(sum.begin(), it_lower);
        //endなら, 残りをはじめからにぶたん, else 引き算する
        ll tmp=0;
        if(it_lower==sum.end()){

        }else{
            tmp = sum[idx_lower]-sum[idx];
        }
        //前の座標と今の座標の差を掛ける
        ans += tmp*(prek>k ? :)

        prek=k;
        idx++;
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