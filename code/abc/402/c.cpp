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
 * 主客転倒
 * i日目には食材B[i]が含まれる料理のみを見て差分更新すればいい なぜなら食材B[i]に関係のない料理については食べられないままか食べられるままであるから
 * 問題では料理->食材のリストが与えられているけど食材->料理のリストに管理しなおす
 */
void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> A(M);
    vector<int> ingCnt(M);
    rep(i, 0, M){
        int K; cin >> K; ingCnt[i] = K;
        rep(j, 0, K){
            int a; cin >> a; a--;
            A[i].push_back(a);
        }
    }
    vector<int> B(N);
    rep(i, 0, N) {
        int b; cin >> b; b--; 
        B[i] = b;
    }

    vector<vector<int>> ingToMeal(N);
    rep(i, 0, M){
        for(int a : A[i]){
            ingToMeal[a].push_back(i);
        }
    }

    int ans = 0;
    rep(i, 0, N){
        //食材B[i]を克服した
        for(int j: ingToMeal[B[i]]){
            ingCnt[j]--;
            if(ingCnt[j] == 0) ans++;
        }
        out(ans);
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