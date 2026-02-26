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
 * 半分全列挙の基礎
 * 計算量はO(N^2*logN)
 * lower_boundで最後のイテレータが返されたときは
 * そのまま配列の添え字に入れるとout of rangeでエラーが出るので注意
 */
// void solve() {
//     ll N, K; cin >> N >> K;
//     vl A(N), B(N),C(N), D(N);
//     rep(i, 0, N) cin >> A[i];
//     rep(i, 0, N) cin >> B[i];
//     rep(i, 0, N) cin >> C[i];
//     rep(i, 0, N) cin >> D[i];
//     vl AB, CD;
//     rep(i, 0, N)rep(j, 0, N) AB.push_back(A[i]+B[j]);
//     rep(i, 0, N)rep(j, 0, N) CD.push_back(C[i]+D[j]);
//     sort(all(AB)); sort(all(CD));
//     // cout << AB.size() << " " << CD.size() << " "<<endl;
//     rep(i, 0, N*N){
//         //CDにK-AB[i]が存在するか判定
//         auto it = lower_bound(all(CD), K-AB[i]);
//         ll idx = distance(CD.begin(), it);
//         if(idx>=N*N) continue;
//         if(CD[idx]==K-AB[i]){
//             Yes;
//             return;
//         }
//     }
//     No;
// }

void solve() {
    ll N, K; cin >> N >> K;
    vl A(N), B(N), C(N), D(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];
    rep(i, 0, N) cin >> C[i];
    rep(i, 0, N) cin >> D[i];
    vl AB, CD;
    rep(i, 0, N)rep(j, 0, N) AB.push_back(A[i]+B[j]);
    rep(i, 0, N)rep(j, 0, N) CD.push_back(C[i]+D[j]);
    sort(all(AB));
    sort(all(CD));
    bool ans = false;
    rep(i, 0, N*N){
        auto it = lower_bound(all(CD), K-AB[i]);
        if(it==CD.end()) continue;
        if(*it==K-AB[i]){
            ans = true;
            break;
        }
    }
    ans ? Yes : No;
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