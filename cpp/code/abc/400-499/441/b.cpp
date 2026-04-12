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
 * ほんとうにやる
 */
void solve() {
// ロジックをちゃんと考える！！！
    int N, M; cin >> N >> M;
    string S, T; cin >> S >> T;
    int Q; cin >> Q;
    vector<string> w(Q);
    rep(i, 0, Q) cin >> w[i];
    rep(i, 0, Q){
        // w[i]に対しての判定
        bool tak=true, aok=true;
        rep(j, 0, sz(w[i])){
            //w[i][j]に対して
            bool tmp_tak=false, tmp_aok=false;
            rep(k, 0, N) if(w[i][j]==S[k]) tmp_tak=true;
            rep(k, 0, M) if(w[i][j]==T[k]) tmp_aok=true;
            if(!tmp_tak)tak=false;
            if(!tmp_aok)aok=false;
        }
        if(tak && aok) out("Unknown");
        else if(tak) out("Takahashi");
        else out("Aoki");
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