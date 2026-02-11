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

// int N, K;
// ll X;
// vector<string> S(N);
// vector<string> ans;

// void dfs(int i, string s){
//     //今からi項目（0-indexed）を決定する。現時点での数列がs。
//     if(i==K){
//         string tmp;
//         rep(i, 0, K){
//             tmp += S[s[i]-'0'];
//         }
//         ans.push_back(tmp);
//         return;
//     }
//     rep(j, 0, N){
//         s.push_back(j+'0');
//         dfs(i+1, s);
//         s.pop_back();
//     }
// }

// /**
//  * DFSで全探索
//  */
// void solve() {
//     cin >> N >> K >> X;
//     S = vector<string>(N);
//     rep(i, 0, N) cin >> S[i];
//     ans = {};

//     //1~Nからなる、長さKの数列を列挙。該当の文字列を構成しansにpush_back
//     dfs(0, "");

//     sort(all(ans));
//     out(ans[X-1]);
// }

/**
 * DFSでN^Kを全探索
 */
void solve() {
    ll N, K, X; cin >> N >> K >> X; X--;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];
    vector<string> ans;
    auto dfs =  [&](auto dfs, ll d, string s) -> void {
        if(d==K){
            ans.push_back(s);
            return;
        }
        rep(i, 0, N){
            dfs(dfs, d+1, s+S[i]);
        }
    };
    dfs(dfs, 0, "");
    sort(all(ans));
    out(ans[X]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // テストケースが1つの場合
    solve();

    // テストケースが複数ある場合 (コメントアウトを外して使用)
    /*
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    */
    return 0;
}