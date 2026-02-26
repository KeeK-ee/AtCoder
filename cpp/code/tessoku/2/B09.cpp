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
/**
 * 二次元imos
 */
void solve() {
    ll N; cin >> N;
    vl A(N), B(N), C(N), D(N);
    rep(i, 0, N) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
        C[i]--;D[i]--;
    }
    vector<vl> XY(1502, vl(1502));
    rep(i, 0, N){
        XY[A[i]][B[i]]++;
        XY[C[i]+1][D[i]+1]++;
        XY[C[i]+1][B[i]]--;
        XY[A[i]][D[i]+1]--;
    }
    vector<vl> imos(1503, vl(1503));
    rep(i, 1, 1503)rep(j, 1, 1503) imos[i][j] = imos[i][j-1] + XY[i-1][j-1];
    rep(j, 1, 1503)rep(i, 1, 1503) imos[i][j] += imos[i-1][j];
    ll ans=0;
    rep(i, 1, 1502)rep(j, 1, 1502)if(imos[i][j]>=1)ans++;
    out(ans);
    // rep(i, 1, 6){
    //     rep(j, 1, 6){
    //         cout << imos[i][j] << " ";
    //     }
    //     cout << endl;
    // }
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