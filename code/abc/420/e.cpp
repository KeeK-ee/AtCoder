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

// #include "../../../ac-library-master/atcoder/dsu.hpp"
#include <atcoder/all>
using namespace atcoder;

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
    ll N, Q;
    cin >> N >> Q;
    dsu uf(N);
    vector<ll> cnt(N); //その頂点をleaderとする連結成分に含まれる黒頂点の個数
    vector<bool> isBlack(N, false); //その頂点が黒かどうか
    rep(qi, 0, Q){
      int op;
      cin >> op;
      if(op==1){
        ll u, v;
        cin >> u >> v;
        u--; v--;
        if(uf.same(u, v)) continue;
        ll lu=uf.leader(u), lv=uf.leader(v);
        uf.merge(u, v);
        ll l=uf.leader(u);
        if(l==lu) {
          cnt[l]+=cnt[lv];
          cnt[lv]=0;
        }
        else {
          cnt[l]+=cnt[lu];
          cnt[lu]=0;
        }
      }
      else if(op==2){
        ll v;
        cin >> v;
        v--;
        isBlack[v] = !isBlack[v];
        if(isBlack[v]) cnt[uf.leader(v)]++;
        else cnt[uf.leader(v)]--;
      }
      else{
        ll v;
        cin >> v;
        v--;
        ll ans=cnt[uf.leader(v)];
        ans<=0 ? No : Yes;
      }
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